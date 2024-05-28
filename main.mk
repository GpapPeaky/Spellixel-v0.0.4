all: resource.o
	g++ -Isrc/include -Lsrc/lib src/main.cpp src/init_win.cpp src/weapon.cpp src/player.cpp src/mesh.cpp src/macros.cpp src/enemy.cpp src/fx.cpp src/map_load.cpp src/item.cpp src/sound.cpp src/font.cpp src/ui.cpp src/utils.cpp obj/resource.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o Spellixell

# RESOURCES FOR COSMETICS, MOSTLY...

resource.o: resources/resource.rc
	windres -o obj/resource.o resources/resource.rc
