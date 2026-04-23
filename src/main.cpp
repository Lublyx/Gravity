#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <GravityEngine.hpp>
#include <Class.hpp>
#include <RenderSphere.hpp>
#include <RenderOrbit.hpp>

// ─────────────────────────────────────────────
//  Constantes
// ─────────────────────────────────────────────
static int WINDOW_WIDTH = 1280;
static int WINDOW_HEIGHT = 720;
static float renderDistance = 1000.0f;
static const std::string WINDOW_TITLE = "Gravity";
int days = 10;
int pause = 0;
double maxFPS = 1.0 / 50.0;
double deltatT = maxFPS * 3600.0 * days;
Sun sun;
Earth earth;
Mars mars;
double earthOrbit = 0.0f;
double marsOrbit = 0.0f;
const double openGlScale = 0.8e10;

struct Camera
{
    float yaw = 0.0f;                // angle horizontal (gauche/droite)
    float pitch = 20.0f;             // angle vertical   (haut/bas)
    float distance = 70.0f;          // distance au centre
    bool dragging = false;           // clic droit enfoncé ?
    double lastX = 0.0, lastY = 0.0; // dernière position souris
} cam;

// ─────────────────────────────────────────────
//  Shaders (inline pour la base)
// ─────────────────────────────────────────────
static const char *VERTEX_SHADER_SRC = R"glsl(
    #version 330 core
    layout(location = 0) in vec3 aPos;

    uniform mat4 uMVP;

    void main()
    {
        gl_Position = uMVP * vec4(aPos, 1.0);
        gl_PointSize = 12.0;
    }
)glsl";

static const char *FRAGMENT_SHADER_SRC = R"glsl(
    #version 330 core
    out vec4 FragColor;

    uniform vec3 uColor;

    void main()
    {
        FragColor = vec4(uColor, 1.0);
    }
)glsl";

// ─────────────────────────────────────────────
//  Callbacks
// ─────────────────────────────────────────────
static void onError(int error, const char *description)
{
    std::cerr << "[GLFW Error " << error << "] " << description << "\n";
}

static void onKey(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE && key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
        days++;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE && key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
        days--;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
        days += 10;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
        days -= 10;
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && days != 0)
    {
        pause = days;
        days = 0;
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && days == 0)
    {
        days = pause;
        pause = 0;
    }
}

static void onResize(GLFWwindow * /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
}

static void onMouseButton(GLFWwindow *window, int button, int action, int /*mods*/)
{
    Camera *cam = (Camera *)glfwGetWindowUserPointer(window);
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        cam->dragging = (action == GLFW_PRESS);
        if (cam->dragging)
        {
            glfwGetCursorPos(window, &cam->lastX, &cam->lastY);
        }
    }
}

static void onMouseMove(GLFWwindow *window, double x, double y)
{
    Camera *cam = (Camera *)glfwGetWindowUserPointer(window);
    if (!cam->dragging)
        return;

    float dx = (float)(x - cam->lastX) * 0.3f;
    float dy = (float)(y - cam->lastY) * 0.3f;
    cam->lastX = x;
    cam->lastY = y;

    cam->yaw += -dx;
    cam->pitch = glm::clamp(cam->pitch + dy, -89.0f, 89.0f);
}

static void onScroll(GLFWwindow *window, double /*dx*/, double dy)
{
    Camera *cam = (Camera *)glfwGetWindowUserPointer(window);
    cam->distance = glm::clamp((float)(cam->distance - dy * 1.0f), 0.5f, 1000.0f);
}

// ─────────────────────────────────────────────
//  Compilation d'un shader
// ─────────────────────────────────────────────
static GLuint compileShader(GLenum type, const char *src)
{
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint ok = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        char log[512];
        glGetShaderInfoLog(id, 512, nullptr, log);
        std::cerr << "[Shader Error] " << log << "\n";
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static GLuint createProgram(const char *vertSrc, const char *fragSrc)
{
    GLuint vert = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        char log[512];
        glGetProgramInfoLog(prog, 512, nullptr, log);
        std::cerr << "[Program Error] " << log << "\n";
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    return prog;
}

// ─────────────────────────────────────────────
//  Main
// ─────────────────────────────────────────────
int main()
{
    // ── Init GLFW ────────────────────────────
    glfwSetErrorCallback(onError);
    if (!glfwInit())
    {
        std::cerr << "Impossible d'initialiser GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing x4

    GLFWwindow *window = glfwCreateWindow(
        WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(), nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Impossible de créer la fenêtre\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // VSync
    glfwSetKeyCallback(window, onKey);
    glfwSetFramebufferSizeCallback(window, onResize);

    // init callback

    glfwSetWindowUserPointer(window, &cam);
    glfwSetMouseButtonCallback(window, onMouseButton);
    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetScrollCallback(window, onScroll);

    // ── Init GLEW ────────────────────────────
    // Note : avec un contexte Core Profile, glewInit() génère un
    // GL_INVALID_ENUM en interne et retourne une erreur même si tout
    // fonctionne. On force glewExperimental, on ignore le retour,
    // et on vide l'erreur spurieuse avec glGetError().
    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    glGetError(); // vide le GL_INVALID_ENUM généré par GLEW
    if (glewErr != GLEW_OK && glewErr != GLEW_ERROR_NO_GLX_DISPLAY)
    {
        std::cerr << "Impossible d'initialiser GLEW : "
                  << glewGetErrorString(glewErr) << "\n";
        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL : " << glGetString(GL_VERSION) << "\n";
    std::cout << "GPU    : " << glGetString(GL_RENDERER) << "\n";

    // ── État OpenGL global ───────────────────
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_PROGRAM_POINT_SIZE); // pour gl_PointSize dans le shader
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // ── Shader ───────────────────────────────
    GLuint shaderProg = createProgram(VERTEX_SHADER_SRC, FRAGMENT_SHADER_SRC);

    // Chaque ligne correspond à 1 point.

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 9 * sizeof(float),
                 nullptr,
                 GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // ── Boucle de rendu ───────────────────────
    double lastTime = glfwGetTime();
    int frames = 0;

    getEarthOrbit(sun, earth, deltatT, earthOrbit);
    getMarsOrbit(sun, mars, deltatT, marsOrbit);

    RenderSphere sunSphere;
    sunSphere.init(7);

    RenderSphere earthSphere;
    earthSphere.init(1.3);

    RenderSphere marsSphere;
    marsSphere.init(0.8);

    RenderOrbit orbit;
    orbit.init();
    float lastRenderTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {

        float currentTime = (float)glfwGetTime();

        if (currentTime - lastRenderTime < maxFPS)
        {
            glfwPollEvents();
            continue; // Skip rendering this frame
        }
        lastRenderTime = currentTime;

        // std::cout << "Sun: " << sun.x << " " << sun.y << " " << sun.z << "\n";
        // std::cout << "Earth: " << earth.x / openGlEarthScale << " " << earth.y / openGlEarthScale << " " << earth.z << "\n";
        // Calcul du FPS dans le titre
        double now = glfwGetTime();
        double diff = now - lastTime;
        frames++;
        if (diff >= 1.0)
        {
            std::string title = WINDOW_TITLE + "  |  " + std::to_string(frames) + " FPS" + "   |   1s = " + std::to_string(days) + " days";
            glfwSetWindowTitle(window, title.c_str());
            frames = 0;
            lastTime = now;
        }
        // deltatT = 3600.0 * days;
        deltatT = maxFPS * 3600.0 * 24 * days;

        // Clear
        glClearColor(0.05f, 0.05f, 0.12f, 1.0f); // fond bleu nuit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // // Dessin des corps
        glUseProgram(shaderProg);

        // calcule cam position

        float yawRad = glm::radians(cam.yaw);
        float pitchRad = glm::radians(cam.pitch);

        glm::vec3 camPos = glm::vec3(
            cam.distance * cos(pitchRad) * sin(yawRad),
            cam.distance * sin(pitchRad),
            cam.distance * cos(pitchRad) * cos(yawRad));

        glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), 0.01f, renderDistance);

        glm::mat4 modelSun = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 MVP = projection * view * modelSun;

        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 1.0f, 0.9f, 0.2f);
        sunSphere.draw();

        glm::mat4 modelEarth = glm::translate(glm::mat4(1.0f),
                                              glm::vec3(earth.x / openGlScale, earth.y / openGlScale, earth.z / openGlScale));
        MVP = projection * view * modelEarth;

        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.20f, 0.65f, 0.89f);
        earthSphere.draw();

        glm::mat4 modelMars = glm::translate(glm::mat4(1.0f),
                                             glm::vec3(mars.x / openGlScale, mars.y / openGlScale, mars.z / openGlScale));
        MVP = projection * view * modelMars;

        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.91f, 0.31f, 0.18f);
        marsSphere.draw();

        glm::mat4 modelOrbitEarth = glm::scale(glm::mat4(1.0f),
                                               glm::vec3(earthOrbit / openGlScale, earthOrbit / openGlScale, earthOrbit / openGlScale));
        MVP = projection * view * modelOrbitEarth;

        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.20f, 0.65f, 0.89f);
        orbit.draw();

        glm::mat4 modelOrbitMars = glm::scale(glm::mat4(1.0f),
                                              glm::vec3(marsOrbit / openGlScale, marsOrbit / openGlScale, marsOrbit / openGlScale));
        MVP = projection * view * modelOrbitMars;

        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.91f, 0.31f, 0.18f);
        orbit.draw();

        calculePosition(sun, earth, mars, deltatT);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // //

        // float vertices[] = {
        //     sun.x,
        //     sun.y,
        //     sun.z, // Soleil (centre)
        //     earth.x / openGlEarthScale,
        //     earth.y / openGlEarthScale,
        //     earth.z / openGlEarthScale, // Terre  (à droite)
        //     mars.x / openGlEarthScale,
        //     mars.y / openGlEarthScale,
        //     mars.z / openGlEarthScale,
        // };

        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        // //

        // // Dessin des corps
        // glUseProgram(shaderProg);
        // glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"),
        //                    1, GL_FALSE, &MVP[0][0]);

        // glBindVertexArray(VAO);
        // // Soleil (jaune)
        // glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 1.0f, 0.9f, 0.2f);
        // glDrawArrays(GL_POINTS, 0, 1);

        // // Terre (bleu)
        // glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.2f, 0.5f, 1.0f);
        // glDrawArrays(GL_POINTS, 1, 1);

        // glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.8f, 0.5f, 1.0f);
        // glDrawArrays(GL_POINTS, 2, 1);

        // glBindVertexArray(0);
    }

    // ── Nettoyage ────────────────────────────
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProg);

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Bye!\n";
    return 0;
}
