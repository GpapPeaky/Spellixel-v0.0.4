CC = g++
SDLF = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
LIBF = -Lsrc/lib
INCF = -Isrc/include
SRCPATH = src/

# SPELLIXEL
SPELLIXEL = Spellixel
SP_FILES = $(SRCPATH)_main.cpp $(SRCPATH)init_win.cpp $(SRCPATH)weapon.cpp $(SRCPATH)player.cpp $(SRCPATH)mesh.cpp $(SRCPATH)enemy.cpp $(SRCPATH)fx.cpp $(SRCPATH)map_load.cpp $(SRCPATH)item.cpp $(SRCPATH)sound.cpp $(SRCPATH)font.cpp $(SRCPATH)ui.cpp $(SRCPATH)utils.cpp
SP_RCOBJ = obj/resource.o

# EDITOR
EDITOR = SpellixelEditor
SE_FILES = $(SRCPATH)editor.cpp
SE_RCOBJ = obj/editor.o

################################################

Spellixel: resource.o
	@echo Compiling Spellixel...
	$(CC) $(LIBF) $(INCF) $(SP_FILES) $(SP_RCOBJ) -o $(SPELLIXEL) $(SDLF)
	Spellixel.exe

resource.o: resources/resource.rc
	windres -o obj/resource.o resources/resource.rc

################################################

Editor: 
	@echo Compiling Spellixel Editor...
	$(CC) $(LIBF) $(INCF) $(SE_FILES) $(SE_RCOBJ) -o $(EDITOR) $(SDLF)
	SpellixelEditor.exe

editor.o: resources/editor.rc
	windres -o obj/editor.o resources/editor.rc

################################################

obj: editor.o resource.o
	@echo Created Resource Object Files...

################################################

clean:
	@echo Cleaning Up...
	del $(SPELLIXEL).exe
	del $(EDITOR).exe
	del map.mdf
	@echo Cleaned Up Successfuly...

# RESOURCES FOR COSMETICS, MOSTLY...
