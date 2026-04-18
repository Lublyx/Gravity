#!/bin/bash
# build.sh — Compile et lance le projet
set -e

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"

echo "==> Création du dossier build..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "==> CMake configure..."
cmake "$PROJECT_DIR" -DCMAKE_BUILD_TYPE=Debug

echo "==> Compilation..."
cmake --build . --parallel "$(nproc)"

echo ""
echo "==> Lancement..."
echo "────────────────────────────────"
./GravitySim