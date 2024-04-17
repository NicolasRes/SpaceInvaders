#ifndef __DONNEES__H__
#define __DONNEES__H__

#include "SDL2/SDL.h"
#include "sdl2-light.h"
#include "constantes.h"

/*
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
    int score;
    int win;
    int gameover; 
    int vague;
    int nb_enemies_current;
    int vitesse_enemies;
    int score_manche;
    int attente;
};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

/**
 * \brief Fonction qui génère un entier aléatoire entre a et b
 * \param a Le premier entier
 * \param b Le deuxième entier
*/
int generate_number (int a,int b );

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 * \param x Coordonnée de l'axe horizontal
 * \param y Coordonnée de l'axe vertical
 * \param w Largeur du sprite
 * \param h Hauteur du sprite
 * \param v Vitesse du sprite
 * \param alv Vérifie si le sprite est en vie
 */
void init_sprite (sprite_t * sprite, int x, int y, int w, int h, int v, int alv);

/**
 * \brief Fonction qui initialise les vaisseaux ennemis
 * \param world Le monde du jeu
*/
void init_enemies(world_t *world);

/**
* \brief Procédure qui rend un sprite visible
* \param sprite Le sprite à rendre visible
*/
void set_visible (sprite_t * sprite);

/**
* \brief Procédure qui rend un sprite invisible
* \param sprite Le sprite à rendre invisible
*/
void set_invisible (sprite_t * sprite);

/**
* \brief Procédure qui affiche les données d'un sprite
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
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world);

/**
 * \brief La fonction qui test le dépassement des limites gauche et droites
 * \param world données du monde
 */
void limite_ecran_joueur(world_t *world);

/**
 * \brief La fonction qui test le dépassement des limites haut et bas
 * \param world données du monde
 */
void limite_ecran_ennemi(world_t *world);

/**
 * \brief Procédure qui gère la collision entre le vaisseau et un ennemi
 * \param sp1 Le joueur
 * \param sp2 Le vaisseau ennemi
*/
void handle_sprites_collision_vaisseau(sprite_t *sp1, sprite_t *sp2);

/**
 * \brief Procédure qui gère la collision avec un missile
 * \param sp1 Le vaisseau du joueur
 * \param sp2 Le missile
*/
void handle_sprites_collision_missile(sprite_t *sp1, sprite_t *sp2,world_t *world);

/**
 * \brief Gère la collision entre le vaisseau et un ennemi avec des hitbox circulaires
 * \param sp1 Le vaisseau joueur
 * \param sp2 le vaisseau ennemi
*/
int sprites_collide_cercle(sprite_t *sp1, sprite_t *sp2);

/**
 * \brief Gère la collision entre le vaisseau et un ennemi avec des hitbox rectangulaires
 * \param sp1 Le vaisseau joueur
 * \param sp2 le vaisseau ennemi
*/
int sprites_collide_rectangle(sprite_t *sp1, sprite_t *sp2);

/**
 * \brief Affiche un message de victoire ou de défaite à la fin du jeu
 * \param world Les données du monde
*/
void MessageVictoire(world_t * world);

/**
 * \brief Implémentation des règles du jeu
 * \param world Les données du monde
*/
void compute_game(world_t *world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world données du monde
 */

void update_data(world_t *world);

#endif