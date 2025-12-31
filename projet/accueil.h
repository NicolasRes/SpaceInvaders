/**
 * @file acceuil.h
 * @brief Définition des fonctions relatives à l'écran d'accueil du jeu.
 */

#ifndef ACCEUIL_H
#define ACCEUIL_H

#include "sdl2-light.h"
#include "constantes.h"
#include "sdl2-ttf-light.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Affiche l'écran d'accueil du jeu.
 *
 * @param window Pointeur vers la fenêtre du jeu.
 * @param renderer Pointeur vers le renderer utilisé pour dessiner sur la fenêtre.
 */
void Creer_Acceuil(SDL_Window *window, SDL_Renderer *renderer);

/**
 * @brief Charge la police de caractères utilisée pour l'écran d'accueil.
 *
 * @return Un pointeur vers la police de caractères chargée.
 */
TTF_Font* charger_police();

/**
 * @brief Charge l'image de fond utilisée pour l'écran d'accueil.
 *
 * @param renderer Pointeur vers le renderer utilisé pour charger l'image.
 * @return Un pointeur vers la texture de l'image de fond chargée.
 */
SDL_Texture* charger_background(SDL_Renderer *renderer);

/**
 * @brief Vérifie si un clic de souris a eu lieu sur un bouton donné.
 *
 * @param x La coordonnée x du clic de souris.
 * @param y La coordonnée y du clic de souris.
 * @param button_x La coordonnée x du coin supérieur gauche du bouton.
 * @param button_y La coordonnée y du coin supérieur gauche du bouton.
 * @param largeur La largeur du bouton.
 * @param hauteur La hauteur du bouton.
 * @return 1 si le clic a eu lieu sur le bouton, 0 sinon.
 */
int Detection_Click_Bouton(int x, int y, int button_x, int button_y, int largeur, int hauteur);

/**
 * @brief Vérifie si la souris survole un bouton donné.
 *
 * @param event_type Le type d'événement SDL.
 * @param button_x La coordonnée x du coin supérieur gauche du bouton.
 * @param button_y La coordonnée y du coin supérieur gauche du bouton.
 * @param largeur La largeur du bouton.
 * @param hauteur La hauteur du bouton.
 * @return 1 si la souris survole le bouton, 0 sinon.
 */
int Passage_bouton(SDL_EventType event_type, int button_x, int button_y, int largeur, int hauteur);

/**
 * @brief Quitte l'application proprement en libérant la mémoire allouée et en fermant les fenêtres.
 *
 * @param window Pointeur vers la fenêtre du jeu.
 * @param renderer Pointeur vers le renderer utilisé pour dessiner sur la fenêtre.
 */
void quitter_application(SDL_Window *window, SDL_Renderer *renderer);

#endif 
