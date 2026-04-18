#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <GravityEngine.hpp>
#include <Class.hpp>

// ─────────────────────────────────────────────
//  Constantes
// ─────────────────────────────────────────────
static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 720;
static const std::string WINDOW_TITLE = "Gravity Simulator";

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
        gl_PointSize = 8.0;
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
}

static void onResize(GLFWwindow * /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
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
    glfwSwapInterval(1); // VSync
    glfwSetKeyCallback(window, onKey);
    glfwSetFramebufferSizeCallback(window, onResize);

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
                 6 * sizeof(float),
                 nullptr,
                 GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // ── Matrice MVP simple (caméra fixe pour l'instant) ──
    glm::mat4 MVP = glm::mat4(1.0f); // identité — on voit la scène en 2D NDC

    // ── Boucle de rendu ───────────────────────
    double lastTime = glfwGetTime();
    int frames = 0;

    Sun sun;
    Earth earth;

    while (!glfwWindowShouldClose(window))
    {
        // std::cout << "Sun: " << sun.x << " " << sun.y << " " << sun.z << "\n";
        // std::cout << "Earth: " << earth.x << " " << earth.y << " " << earth.z << "\n";
        // Calcul du FPS dans le titre
        double now = glfwGetTime();
        double diff = now - lastTime;
        frames++;
        if (diff >= 1.0)
        {
            std::string title = WINDOW_TITLE + "  |  " + std::to_string(frames) + " FPS";
            glfwSetWindowTitle(window, title.c_str());
            frames = 0;
            lastTime = now;
        }

        // Clear
        glClearColor(0.05f, 0.05f, 0.12f, 1.0f); // fond bleu nuit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //

        float vertices[] = {
            sun.x,
            sun.y,
            sun.z, // Soleil (centre)
            earth.x,
            earth.y,
            earth.z, // Terre  (à droite)
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        calculePosition(sun, earth);
        //

        // Dessin des corps
        glUseProgram(shaderProg);
        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"),
                           1, GL_FALSE, &MVP[0][0]);

        glBindVertexArray(VAO);
        // Soleil (jaune)
        glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 1.0f, 0.9f, 0.2f);
        glDrawArrays(GL_POINTS, 0, 1);

        // Terre (bleu)
        glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.2f, 0.5f, 1.0f);
        glDrawArrays(GL_POINTS, 1, 1);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
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
