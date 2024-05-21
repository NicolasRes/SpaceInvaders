CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h constantes.h donnees.h graphique.h sdl2-ttf-light.h accueil.h 
SRC = main.c sdl2-light.c donnees.c graphique.c sdl2-ttf-light.c accueil.c 
OBJ = $(SRC:%.c=%.o)

PROG = spacebattle

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	
doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html

tests:
	gcc test.c donnees.o -o test `sdl2-config --libs` -lSDL2_ttf -lm
	./test
