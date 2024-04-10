#ifndef __GRAPHIQUE__H__
#define __GRAPHIQUE__H__

#include "sdl2-light.h"
#include "donnees.h"
#include "constantes.h"



/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* player;
    SDL_Texture* v_ennemi;
    SDL_Texture* missile;
};

/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;


void clean_textures(textures_t *textures);

void  init_textures(SDL_Renderer *renderer, textures_t *textures);

void apply_background(SDL_Renderer *renderer, textures_t *textures);

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world);

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

#endif