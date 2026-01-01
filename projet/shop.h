/* shop.h */
#ifndef SHOP_H
#define SHOP_H

#include <SDL2/SDL.h>
#include "donnees.h"
#include "graphique.h"

/**
 * \brief Lance le shop entre deux vagues
 * \details Affiche une interface d'achat basée sur world->gold et les bonus
 *          Sort quand le joueur choisit "CONTINUER" (clic / Entrée / Échap)
 *          Met world->state = STATE_PLAY à la sortie (la vague suivante est gérée par main)
 *
 * \param window Fenêtre SDL
 * \param renderer Renderer SDL
 * \param world Données du monde (gold, bonus, cooldown, etc.)
 * \param textures Textures + font déjà chargées (utilise textures->font, textures->background si dispo)
 */
void shop_run(SDL_Window *window, SDL_Renderer *renderer, world_t *world, textures_t *textures);

#endif