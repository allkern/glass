$SDL2_DIR = "C:\Users\Lisandro\Desktop\Development\Libraries\SDL2"

md -Force -Path bin > $null

c++ -I"`"$($SDL2_DIR)\include\SDL2`"" `
    -I"`"$($SDL2_DIR)\include`"" `
    "image.cpp" `
    -o "image.exe" `
    -L"`"$($SDL2_DIR)\lib\x64`"" `
    -m64 -lSDL2main -lSDL2 -lopengl32 -g -std=c++2a -Wno-unused-variable