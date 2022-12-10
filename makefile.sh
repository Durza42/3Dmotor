g++ -c include/miscellaneous/menu.cpp -o include/miscellaneous/menu.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c include/miscellaneous/imgs.cpp -o include/miscellaneous/imgs.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c menus.cpp -o menus.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c field_menu.cpp -o field_menu.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c main.cpp -o main.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c main_class.cpp -o main_class.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c Input.cpp -o Input.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c sol.cpp -o sol.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c mur.cpp -o mur.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c light.cpp -o light.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c utilities.cpp -o utilities.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c Shader.cpp -o Shader.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c Texture.cpp -o Texture.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c camera.cpp -o camera.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c hitbox.cpp -o hitbox.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg
g++ -c labyrinthe.cpp -o labyrinthe.o `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -g -pg

g++ main.o Input.o main_class.o utilities.o Shader.o Texture.o camera.o light.o sol.o mur.o hitbox.o labyrinthe.o menus.o field_menu.o include/miscellaneous/menu.o include/miscellaneous/imgs.o -o jeu.out `sdl2-config --libs` -lglut -lGLU -lGL -lGLEW -lSDL2_ttf -lSDL2_mixer -lSDL2_image -g -pg

./jeu.out
