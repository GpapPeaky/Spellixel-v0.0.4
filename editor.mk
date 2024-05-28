all: editor.o
	g++ -Isrc/include -Lsrc/lib src/editor.cpp obj/editor.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o editor

# RESOURCES FOR COSMETICS, MOSTLY...

editor.o: resources/editor.rc
	windres -o obj/editor.o resources/editor.rc

