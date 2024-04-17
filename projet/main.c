/**
 * \file main.c
 * \brief Programme principal initial du niveau 2
 * \author  Mathias et Nicolas 
 * \version 1.0
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "sdl2-light.h"
#include "graphique.h"
#include "donnees.h"
#include <time.h>
#include "acceuil.h"

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] ){
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    srand(time(NULL)) ;
    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    printf("--------------------Debut Partie--------------------\n");
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(17);
    }
    MessageVictoire(&world);
    pause(TEMPS);
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    return 0;
}