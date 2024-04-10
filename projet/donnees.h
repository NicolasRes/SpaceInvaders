#ifndef __DONNEES__H__
#define __DONNEES__H__

#include "SDL2/SDL.h"

/**
*\brief structure pour représenter le vaisseau
*\a x Horizontal
*\a y Vertical
*\a h Hauteur
*\a w Largeur
*\a v Vitesse
*/

struct sprite_s {
    int x;
    int y;
    int h;
    int w;
    int v;
    int is_visible;
    int is_alive;
};

typedef struct sprite_s sprite_t;


/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    
    sprite_t * vaisseau;
    sprite_t * v_ennemi;
    sprite_t * missile;

    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;


void init_sprite (sprite_t * sprite, int x, int y, int w, int h, int v, int alv);


void set_visible (sprite_t * sprite);

void set_invisible (sprite_t * sprite);

void print_sprite (sprite_t * sprite);

void init_data(world_t * world);

void clean_data(world_t *world);

int is_game_over(world_t *world);

void update_data(world_t *world);

void handle_events(SDL_Event *event,world_t *world);

void limite_ecran_joueur(world_t *world);

void limite_ecran_ennemi(world_t *world);




#endif