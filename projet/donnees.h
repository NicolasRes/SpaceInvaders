#ifndef __DONNEES__H__
#define __DONNEES__H__

#include "SDL2/SDL.h"
#include "sdl2-light.h"
#include "constantes.h"
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
    //sprite_t * v_ennemi;
    sprite_t * missile;
    sprite_t ** enemies;
    int nb_v_out;
    int  score;
    int win;

    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_sprite (sprite_t * sprite, int x, int y, int w, int h, int v, int alv);

/**
* \brief Procédure qui rend un sprite visible
*/
void set_visible (sprite_t * sprite);

/**
* \brief Procédure qui rend un sprite invisible
*/
void set_invisible (sprite_t * sprite);

/**
* \brief 
*/
void print_sprite (sprite_t * sprite);

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
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
 * \param world données du monde
 */

void update_data(world_t *world);


/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world);

/**
 * \brief La fonction qui test le dépassement des limites gauche et droites
 * \param wolrd données du monde
 */
void limite_ecran_joueur(world_t *world);

/**
 * \brief La fonction qui test le dépassement des limites haut et bas
 * \param wolrd données du monde
 */
void limite_ecran_ennemi(world_t *world);

void handle_sprites_collision_vaisseau(sprite_t *sp1, sprite_t *sp2);

void handle_sprites_collision_missile(sprite_t *sp1, sprite_t *sp2,world_t *world);

int sprites_collide_cercle(sprite_t *sp1, sprite_t *sp2);

int sprites_collide_rectangle(sprite_t *sp1, sprite_t *sp2);

int generate_number (int a,int b );

void init_enemies(world_t *world);

void MessageVictoire(world_t * world);

void compute_game(world_t *world);

#endif