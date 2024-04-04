#ifndef DONNEES_H
#define DONNEES_H

#include "sdl2-light.h"


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
};

typedef struct sprite_s sprite_t;


/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    
    sprite_t * vaisseau;
    sprite_t * Vennemi; 
    sprite_t * Missile; 


    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;


/**
* \brief Affiche les données du sprite
*/
void print_sprite (sprite_t * sprite);


/**
* \brief Rend un sprite visible
*/
void set_visible( sprite_t * sprite);

/**
* \brief Rend un sprite visible
*/
void set_invisible( sprite_t * sprite);

/**
* \brief Initialise les données du monde
*/
void init_data(world_t * world);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */

void clean_data(world_t *world);


/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world);


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world);

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world);







#endif