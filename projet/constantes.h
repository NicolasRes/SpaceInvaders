#ifndef CONSTANTES_H
#define CONSTANTES_H


/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 600

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 960


/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_ACC_WIDTH 200

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_ACC_HEIGHT 300


#define WHITE (SDL_Color){255, 255, 255}


#define GREEN (SDL_Color){0, 255, 0}


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32

/**
 * \brief Taille du missile
*/

#define MISSILE_SIZE 8

/**
* \brief Vitesse de l'ennemi
*/
#define ENEMY_SPEED 1

/**
 * \brief Vitesse du vaisseau
*/
#define VAISSEAU_SPEED 7

/**
* \brief Vitesse du missile
*/
#define MISSILE_SPEED 12

/**
* \brief Nombre d'ennemis
*/
#define NB_ENEMIES 1

/**
 * \brief Distance verticale entre les vaisseaux
*/
#define VERTICAL_DIST 2*SHIP_SIZE

/**
 * \brief Temps d'attente avant fermeture du jeu
*/
#define TEMPS 2000

#endif