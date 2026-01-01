/**
 * \file main.c
 * \brief Programme principal
 * \author Nicolas
 * \version 1.1
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "sdl2-light.h"
#include "graphique.h"
#include "donnees.h"
#include <time.h>
#include "accueil.h"
#include "shop.h"

// Fonctions auxiliaires pour la lisibilité de la fonction main

static void play(SDL_Event *event, world_t *world, SDL_Renderer *renderer, textures_t *textures) {
    handle_events(event, world);
    update_data(world);
    refresh_graphics(renderer, world, textures);
    pause(17);
}

// Appelée quand on quitte le shop pour lancer la vague suivante
static void start_next_wave(world_t *world) {
    MiseAJour_Vague(world);
    init_enemies(world);
    world->state = STATE_PLAY;
}

static void menu(SDL_Event *event, world_t *world, SDL_Renderer *renderer, textures_t *textures, SDL_Window *window) {
    (void)event; (void)renderer; (void)textures; (void)window;
    world->state = STATE_PLAY;
}

/**
 *  \brief Programme principal qui implémente la boucle du jeu
 */


int main(int argc, char* args[]){
    ///// Paramètres inutilisés /////
    (void)argc;
    (void)args;
    ////////////////////////////////

    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    srand(time(NULL)) ;
    //initialisation du jeu
    init(&window,&renderer,&textures,&world);

    printf("--------------------Debut Partie--------------------\n");
    while(!is_game_over(&world)){ // tant que le jeu n'est pas fini

        switch (world.state) {

            case STATE_MENU:
                menu(&event, &world, renderer, &textures, window);
                break;

            case STATE_PLAY:
                play(&event, &world, renderer, &textures);
                break;

            case STATE_SHOP:
                shop_run(window, renderer, &world, &textures);
                if (world.state == STATE_PLAY) {
                    start_next_wave(&world);
                }
                break;

            case STATE_GAMEOVER:
                world.gameover = 1;
                break;

            default:
                // sécurité
                world.gameover = 1;
                break;
        }
    }
    MessageVictoire(&world);
    GameOver(renderer, &textures);
    pause(TEMPS);
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    return 0;
}