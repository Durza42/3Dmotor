i686-w64-mingw32-g++-win32 -c menus.cpp -o menus.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c field_menu.cpp -o field_menu.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c main.cpp -o main.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c main_class.cpp -o main_class.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c Input.cpp -o Input.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c sol.cpp -o sol.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c mur.cpp -o mur.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c light.cpp -o light.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c utilities.cpp -o utilities.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c Shader.cpp -o Shader.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c Texture.cpp -o Texture.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c camera.cpp -o camera.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c hitbox.cpp -o hitbox.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg
i686-w64-mingw32-g++-win32 -c labyrinthe.cpp -o labyrinthe.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW  -Iinclude -Llib -g -pg

i686-w64-mingw32-g++-win32 main.o Input.o main_class.o utilities.o Shader.o Texture.o camera.o light.o sol.o mur.o hitbox.o labyrinthe.o menus.o field_menu.o -o jeu.out `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -lSDL2_ttf -lSDL2_mixer -lSDL2_image  -Iinclude -Llib -g -pg

./jeu.exe


## i686-w64-mingw32-g++  main.cpp -Iinclude -Llib -w -Wall -Wextra -std=c++17 -lSDL2 -o main
## -Iinclude
## -Llib
