#ifndef ETAT_H
#define ETAT_H

/**
 * @brief Structure pour représenter les états du jeu
 * 
 */
typedef enum {
    STATE_MENU,
    STATE_PLAY,
    STATE_SHOP,
    STATE_GAMEOVER
} game_state_t;

#endif