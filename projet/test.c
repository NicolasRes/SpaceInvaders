#include"donnees.h"
#include "constantes.h"
#include <stdlib.h>
#include <stdio.h>


/**
* \brief Procédure paramètres pour tester l'initialisation d'un sprite
*/
void test_init_sprite_param(sprite_t * sprite_test, int x, int y, int w, int h, int v, int alive){

    sprite_test = malloc(sizeof(sprite_t));
    init_sprite(sprite_test, x, y, w, h, v, alive);

    print_sprite(sprite_test);
    printf("\n");

}


/**
* \brief Procédure qui teste l'initialisation d'un sprite
*/
void test_init_sprite() {
    sprite_t * sp;
    test_init_sprite_param(sp, 50, 45, 100, 80, 2, 1);
    test_init_sprite_param(sp, 30, 20, 50, 30, 10, 1);
    test_init_sprite_param(sp, 10, 10, 80, 20, 0, 0);

}


/**
* \brief Procédure paramètres pour tester la bordure droite du monde
*/
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

/**
* \brief Procédure paramètres pour tester la bordure gauche du monde
*/
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

/**
* \brief Procédure qui teste les bordures du monde
*/
void test_bordure() {
    world_t *world;

    world->vaisseau = malloc(sizeof(sprite_t));

    init_sprite(world->vaisseau, 50, 45, 100, 80, 2, 1);
    //test_bordure_droite_param(&world);
    test_bordure_gauche_param(world);
    free(world->vaisseau);
    free(world);
}

/**
* \brief Procédure qui teste la collision de deux sprites avec des hitbox circulaires
*/
void test_sprites_collide_cercle() {
    sprite_t *sprite1_collision = malloc(sizeof(sprite_t));
    sprite_t *sprite2_collision = malloc(sizeof(sprite_t));
    sprite_t *sprite1_pas_collision = malloc(sizeof(sprite_t));
    sprite_t *sprite2_pas_collision = malloc(sizeof(sprite_t));

    init_sprite(sprite1_collision, 50, 50, 20, 20, 0, 1);
    init_sprite(sprite2_collision, 55, 55, 20, 20, 0, 1);

    init_sprite(sprite1_pas_collision, 50, 50, 20, 20, 0, 1);
    init_sprite(sprite2_pas_collision, 100, 100, 20, 20, 0, 1);

    printf("Collision :\n");
    printf("Sprite 1 : ");
    print_sprite(sprite1_collision);
    printf("Sprite 2 : ");
    print_sprite(sprite2_collision);

    int collision = sprites_collide_cercle(sprite1_collision, sprite2_collision);  
    if (collision) {
        printf("Collision détectée !\n");
    } else {
        printf("Pas de collision détectée.\n");
    }

    printf("\nPas de collision :\n");
    printf("Sprite 1 : ");
    print_sprite(sprite1_pas_collision);
    printf("Sprite 2 : ");
    print_sprite(sprite2_pas_collision);

    collision = sprites_collide_cercle(sprite1_pas_collision, sprite2_pas_collision);
    if (collision) {
        printf("Collision détectée !\n");
    } else {
        printf("Pas de collision détectée.\n");
    }

    free(sprite1_collision);
    free(sprite2_collision);
    free(sprite1_pas_collision);
    free(sprite2_pas_collision);
}

/**
* \brief Procédure qui teste la collision entre deux sprites
*/
void test_handle_sprites_collision() {
    sprite_t * sprite1;
    sprite_t * sprite2;

    sprite1 = malloc(sizeof(sprite_t));
    sprite2 = malloc(sizeof(sprite_t));

    init_sprite(sprite1, 50, 50, 20, 20, 0, 1);
    init_sprite(sprite2, 55, 55, 20, 20, 0, 1);

    test_sprites_collide_cercle(sprite1, sprite2);

    if (sprite1->is_alive == 0 && sprite2->is_alive == 0) {
        printf("Il y a eu collision -> suppression sprite !\n");
    } else {
        printf("Pas de collision détectée.\n");
    }
}

void test_init_enemies(){
    world_t *world = malloc(sizeof(world_t));
    
    init_enemies(world);
    
    for(int j=0;j<NB_ENEMIES;j++){
        print_sprite(world->enemies[j]);
        printf("\n");
    }
    
    for (int i=0;i<NB_ENEMIES;i++){
        (world->enemies[i]);
    }
    free(world->enemies);
   
}

#undef main


int main( int argc, char* args[] ){

    //test_init_sprite();
    //test_bordure();
    //test_sprites_collide_cercle();
    //test_handle_sprites_collision();
    test_init_enemies();
}