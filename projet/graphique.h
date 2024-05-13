/**
 * @file graphique.h
 * @brief Définition des fonctions relatives à la gestion graphique du jeu.
 */

#ifndef __GRAPHIQUE__H__
#define __GRAPHIQUE__H__

#include "sdl2-light.h"
#include "donnees.h"
#include "constantes.h"
#include "sdl2-ttf-light.h"
#include <stdlib.h>
#include <stdio.h>
#include "accueil.h"

/**
 * @brief Structure pour stocker les textures utilisées dans le jeu.
 */
typedef struct {
    SDL_Texture *background; /**< Texture du fond d'écran */
    SDL_Texture *player; /**< Texture du joueur */
    SDL_Texture *v_ennemi; /**< Texture de l'ennemi */
    SDL_Texture *missile; /**< Texture du missile */
    TTF_Font *font; /**< Police de caractères */
} textures_t;

/**
 * @brief Libère la mémoire allouée pour les textures.
 *
 * @param textures Pointeur vers la structure de textures.
 */
void clean_textures(textures_t *textures);

/**
 * @brief Initialise les textures du jeu.
 *
 * @param renderer Pointeur vers le renderer utilisé.
 * @param textures Pointeur vers la structure de textures à initialiser.
 */
void init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
 * @brief Change la taille d'une texture.
 *
 * @param renderer Pointeur vers le renderer utilisé.
 * @param texture_ptr Pointeur vers la texture à redimensionner.
 * @param textures Pointeur vers la structure de textures.
 * @param longueur La nouvelle longueur de la texture.
 * @param largeur La nouvelle largeur de la texture.
 */
void Changer_taille_image(SDL_Renderer *renderer, SDL_Texture **texture_ptr, textures_t *textures, int longueur, int largeur);

/**
 * @brief Applique le fond d'écran.
 *
 * @param renderer Pointeur vers le renderer utilisé.
 * @param textures Pointeur vers la structure de textures.
 */
void apply_background(SDL_Renderer *renderer, textures_t *textures);

/**
 * @brief Convertit un entier en chaîne de caractères.
 *
 * @param value L'entier à convertir.
 * @return La chaîne de caractères représentant l'entier.
 */
char* int_to_string (int value);

/**
 * @brief Applique la texture d'un sprite.
 *
 * @param renderer Pointeur vers le renderer utilisé.
 * @param texture Pointeur vers la texture du sprite.
 * @param sprite Pointeur vers la structure du sprite.
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

#endif