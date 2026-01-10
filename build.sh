#!/bin/bash

# Build script for PedestriansTragedy on macOS

echo "Building PedestriansTragedy..."

# Create build directory
mkdir -p build

# Compile all source files
echo "Compiling source files..."
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/Actor.cpp -o build/Actor.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/Agent.cpp -o build/Agent.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/Coin.cpp -o build/Coin.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/Main.cpp -o build/Main.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/Pawn.cpp -o build/Pawn.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/SoundManager.cpp -o build/SoundManager.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/Vertex.cpp -o build/Vertex.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/World.cpp -o build/World.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/WorldObject.cpp -o build/WorldObject.o
g++ -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include -c source/WavLoader.cpp -o build/WavLoader.o

# Link
echo "Linking..."
g++ build/*.o -framework OpenGL -framework GLUT -framework OpenAL -o PedestriansTragedy

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Run with: ./PedestriansTragedy"
else
    echo "Build failed!"
    exit 1
fi
