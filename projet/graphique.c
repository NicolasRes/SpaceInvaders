#include "graphique.h"


void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->player);
    clean_texture(textures->v_ennemi);
    clean_texture(textures->missile);
}

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->player = load_image("ressources/spaceship.bmp",renderer);
    textures->background = load_image("ressources/space-background.bmp",renderer);
    textures->v_ennemi = load_image("ressources/enemy.bmp",renderer);
    textures->missile = load_image("ressources/missile.bmp",renderer);
}


void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}



void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    /* A COMPLETER */

    //Applicaiton des textures du sprite dans le renderer
    apply_sprite(renderer, textures->player, world->vaisseau);

    //Applicaiton des textures de l'v_ennemi dans le renderer
    apply_sprite(renderer, textures->v_ennemi, world->v_ennemi);

    //Applicaiton des textures du missile dans le renderer
    apply_sprite(renderer, textures->missile, world->missile);
    
    // on met à jour l'écran
    update_screen(renderer);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {

    if (sprite->is_visible == 1 ) {
        if (sprite->is_alive==1){
            apply_texture(texture, renderer, sprite->x, sprite->y);
        }
        
    }
}


void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}