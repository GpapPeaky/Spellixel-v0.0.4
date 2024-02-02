all: resource.o
	g++ -Isrc/include -Lsrc/lib editor.cpp resource.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o editor

# RESOURCES FOR COSMETICS, MOSTLY...

resource.o: resource.rc
	windres -o resource.o resource.rc