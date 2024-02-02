all: editor.o
	g++ -Isrc/include -Lsrc/lib editor.cpp editor.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o editor

# RESOURCES FOR COSMETICS, MOSTLY...

editor.o: editor.rc
	windres -o editor.o editor.rc
