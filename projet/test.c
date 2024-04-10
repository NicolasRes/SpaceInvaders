
#include"donnees.h"
//#include "constantes.h"
#include <stdlib.h>
#include <stdio.h>



void test_init_sprite_param(){

    sprite_t *sprite_test;
    sprite_test= malloc(sizeof(sprite_t));
    init_sprite(sprite_test,50,45, 100,80, 2,1);

    print_sprite(sprite_test);

}



#undef main


int main( int argc, char* args[] ){

    test_init_sprite_param();

}