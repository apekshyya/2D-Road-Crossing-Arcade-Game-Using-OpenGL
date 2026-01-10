#!/bin/bash

# Build script for roadcrossing on macOS
# Road Crossing Game - Cross the road safely!

echo "Building roadcrossing..."

# Create build directory
mkdir -p build

# Compile flags with OpenAL deprecation suppressed
COMPILE_FLAGS="-std=c++11 -Wall -DGL_SILENCE_DEPRECATION -Wno-deprecated-declarations -I./include"

# Compile all source files
echo "Compiling source files..."
g++ $COMPILE_FLAGS -c source/Actor.cpp -o build/Actor.o
g++ $COMPILE_FLAGS -c source/Agent.cpp -o build/Agent.o
g++ $COMPILE_FLAGS -c source/Coin.cpp -o build/Coin.o
g++ $COMPILE_FLAGS -c source/Main.cpp -o build/Main.o
g++ $COMPILE_FLAGS -c source/Pawn.cpp -o build/Pawn.o
g++ $COMPILE_FLAGS -c source/SoundManager.cpp -o build/SoundManager.o
g++ $COMPILE_FLAGS -c source/Vertex.cpp -o build/Vertex.o
g++ $COMPILE_FLAGS -c source/World.cpp -o build/World.o
g++ $COMPILE_FLAGS -c source/WorldObject.cpp -o build/WorldObject.o
g++ $COMPILE_FLAGS -c source/WavLoader.cpp -o build/WavLoader.o

# Link
echo "Linking..."
g++ build/*.o -framework OpenGL -framework GLUT -framework OpenAL -o roadcrossing

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Run with: ./roadcrossing"
else
    echo "Build failed!"
    exit 1
fi
