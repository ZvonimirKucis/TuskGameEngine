@echo off
REM Run from root directory!
if not exist "build\shaders\" mkdir "build\shaders"

echo "Compiling shaders..."
echo "main.vert.glsl -> build/shaders/main.vert.spv"
glslc.exe -fshader-stage=vert main.vert.glsl.txt -o build/shaders/main.vert.spv
glslc.exe -fshader-stage=vert main.vert.glsl_2.txt -o build/shaders/main.vert_2.spv
echo "main.frag.glsl -> build/shaders/main.frag.spv"
glslc.exe -fshader-stage=frag main.frag.glsl.txt -o build/shaders/main.frag.spv

echo "Done."