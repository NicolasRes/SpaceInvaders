CFLAGS =  -O3 -Dmain=SDL_main
LDFLAGS = -lm -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
SDL2_INCLUDE_DIR = C:/SDL2-2.0.12/x86_64-w64-mingw32/include/
SDL2_LIBRARIES_DIR = C:/SDL2-2.0.12/x86_64-w64-mingw32/lib

INC = sdl2-light.h constantes.h donnees.h graphique.h sdl2-ttf-light.h accueil.h controler.h
SRC = main.c sdl2-light.c donnees.c graphique.c sdl2-ttf-light.c accueil.c controler.c
OBJ = $(SRC:%.c=%.o)

PROG = spacebattle.exe

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<  -I $(SDL2_INCLUDE_DIR)

$(PROG): $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@ -L $(SDL2_LIBRARIES_DIR)

doc: $(PROG)
	doxygen $(PROG)

.PHONY: clean
clean:
	del /f /q *.o *~ $(PROG)
	rd /s /q latex html

tests:
	gcc test.c donnees.o -o test -I $(SDL2_INCLUDE_DIR) -L $(SDL2_LIBRARIES_DIR) -lm -lmingw32 -lSDL2main -lSDL2
	./test
