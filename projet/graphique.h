#ifndef __GRAPHIQUE__H__
#define __GRAPHIQUE__H__

#include "sdl2-light.h"
#include "donnees.h"
#include "constantes.h"
#include "sdl2-ttf-light.h"
#include <stdlib.h>

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* player;
    SDL_Texture* v_ennemi;
    SDL_Texture* missile;
    TTF_Font * font;
};

/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures);

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void  init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_background(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

/**
 * \brief Applique la texture des ennemis sur le renderer
 * \param renderer la surface de l'écran dee jeu
 * \param world les données du monde
 * \param textures les textures
*/
void apply_enemies(SDL_Renderer *renderer,world_t * world,textures_t *textures)

/**
 * \brief Transforme un entier en chaine de caractères
 * \param value La valleur de l'entier à transformer (en base 10)
*/
char* int_to_string (int value)

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param renderer le renderer
 * \param textures les textures
 * \param sprite le sprite qu el'on doit appliquer
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

/**
 * \brief Fonction qui nettoie les textures / données du jeu
 * \param window La fenêtre de jeu
 * \param renderer Le renderer
 * \param textures Les textures du jeu
 * \param world Les données du jeu
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world);



char* int_to_string(int value);

#endif