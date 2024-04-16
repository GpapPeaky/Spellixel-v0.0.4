all: resource.o
	g++ -Isrc/include -Lsrc/lib main.cpp init_win.cpp weapon.cpp player.cpp mesh.cpp macros.cpp enemy.cpp fx.cpp map_load.cpp item.cpp sound.cpp font.cpp ui.cpp utils.cpp resource.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o Spellixell

# RESOURCES FOR COSMETICS, MOSTLY...

resource.o: resource.rc
	windres -o resource.o resource.rc
