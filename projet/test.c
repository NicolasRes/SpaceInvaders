
#include"donnees.h"
#include "constantes.h"
#include <stdlib.h>
#include <stdio.h>



void test_init_sprite_param(sprite_t * sprite_test, int x, int y, int w, int h, int v, int alive){

    sprite_test = malloc(sizeof(sprite_t));
    init_sprite(sprite_test, x, y, w, h, v, alive);

    print_sprite(sprite_test);
    printf("\n");

}

void test_init_sprite() {
    sprite_t * sp;
    test_init_sprite_param(sp, 50, 45, 100, 80, 2, 1);
    test_init_sprite_param(sp, 30, 20, 50, 30, 10, 1);
    test_init_sprite_param(sp, 10, 10, 80, 20, 0, 0);

}


void test_bordure_droite_param(world_t * world) {

    printf("Données initiales : ");
    print_sprite(world->vaisseau);
    printf("\n");

    printf("XdroiteMax = Taille écran - Largeur du sprite = %d\n", SCREEN_WIDTH - world->vaisseau->w);

    printf("Déplacement de X vers la droite : ");
    int choix = -1;
    int longueur;

    while(choix != 0) {
        printf("Saisir longueur à ajouter à x : \n\n");
        scanf("%d", &longueur);
        world->vaisseau->x += longueur;
        printf("XdroiteMax = Taille écran - Largeur du sprite = %d\n", SCREEN_WIDTH - world->vaisseau->w);

        printf("Longueur après déplacement : \n\n");
        print_sprite(world->vaisseau);

        limite_ecran_joueur(world);
        printf("Test fonction bordure :\n");
        print_sprite(world->vaisseau);
        printf("1 pour retester, 0 pour arreter : \n");
        scanf("%d", &choix);
    }

}


void test_bordure_gauche_param(world_t * world) {

    printf("Données initiales : \n");
    print_sprite(world->vaisseau);
    printf("\n");

    printf("XgaucheMax = 0\n");

    printf("Déplacement de X vers la gauche : ");
    int choix = -1;
    int longueur;

    while(choix != 0) {
        printf("Saisir longueur à soustraire à x : \n\n");
        scanf("%d", &longueur);
        world->vaisseau->x -= longueur;
        printf("XgaucheMax = 0");

        printf("Longueur après déplacement : \n\n");
        print_sprite(world->vaisseau);

        limite_ecran_joueur(world);
        printf("Test fonction bordure :\n");
        print_sprite(world->vaisseau);
        printf("1 pour retester, 0 pour arreter : \n");
        scanf("%d", &choix);
    }

}


void test_bordure() {
    world_t world;

    world.vaisseau = malloc(sizeof(sprite_t));

    init_sprite(world.vaisseau, 50, 45, 100, 80, 2, 1);
    //test_bordure_droite_param(&world);
    test_bordure_gauche_param(&world);
    free(world.vaisseau);
}




#undef main


int main( int argc, char* args[] ){

    //test_init_sprite();
    test_bordure();

}