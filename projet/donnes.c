#include "constantes.h"
#include "donnees.h"



/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */

void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v){

    sprite->x =x;
    sprite->y =y;
    sprite->w =w;
    sprite->h =h;
    sprite->v =v;
    sprite->is_visible=1;
}


/**
* \brief Affiche les données du sprite
*/
void print_sprite (sprite_t * sprite) {
    printf("Coordonnée x : %d\n", sprite->x);
    printf("Coordonnée y : %d\n", sprite->y);
    printf("Hauteur : %d\n", sprite->h);
    printf("Largeur : %d\n", sprite->w);
    printf("Vitesse : %d\n", sprite->v);
}


/**
* \brief Rend un sprite visible
*/
void set_visible( sprite_t * sprite){
    sprite->is_visible=1;
    
}

/**
* \brief Rend un sprite visible
*/
void set_invisible( sprite_t * sprite){
    sprite->is_visible=0;
}

/**
* \brief Initialise les données du monde
*/
void init_data(world_t * world){
    world->vaisseau = malloc(sizeof(sprite_t));
    world->Vennemi = malloc(sizeof(sprite_t));
    world->Missile = malloc(sizeof(sprite_t));

    init_sprite (world->vaisseau, (SCREEN_WIDTH/2)-(SHIP_SIZE/2), SCREEN_HEIGHT-(SHIP_SIZE*3/2), SHIP_SIZE, SHIP_SIZE, 5);
    print_sprite(world->vaisseau);
    //on n'est pas à la fin du jeu
    
    init_sprite(world->Vennemi,(SCREEN_WIDTH/2)-(SHIP_SIZE/2),SHIP_SIZE/2,SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED);
    //print_sprite(world->Vennemi);

    init_sprite (world->Missile, world->vaisseau->x +SHIP_SIZE/2 -MISSILE_SIZE/2 , world->vaisseau->y - MISSILE_SIZE, SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED);
    set_invisible(world->Missile);
    print_sprite(world->Missile);

    world->gameover = 0;
}   




/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    world->Vennemi->y+=world->Vennemi->v;
    if(world->Missile->is_visible==1){
        world->Missile->y-=world->Missile->v;
    }

}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
        
        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'D'
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'D'
            if(event->key.keysym.sym == SDLK_d){
                world->vaisseau->x+=world->vaisseau->v;
            }
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'Q'
            if(event->key.keysym.sym == SDLK_q){
                world->vaisseau->x-=world->vaisseau->v;
            }
        }

        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'Q'
            if(event->key.keysym.sym == SDLK_SPACE){
                world->Missile->x=world->vaisseau->x +SHIP_SIZE/2 -MISSILE_SIZE/2;

                world->Missile->is_visible=1;
            }
        }

    }
}
