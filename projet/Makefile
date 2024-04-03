CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h
SRC = main.c sdl2-light.c
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
<<<<<<< HEAD
	rm -rf latex html

=======
	rm -rf latex html
>>>>>>> 3fa61474b780e268285a51c3c9597d8c4f80c183
