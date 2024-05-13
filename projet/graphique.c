#include "graphique.h"
#include "controler.h"

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->player);
    clean_texture(textures->v_ennemi);
    clean_texture(textures->missile);
    clean_font(textures->font);
}

void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->player = load_image("ressources/spaceship.bmp",renderer);
    textures->background = load_image("ressources/space-background.bmp",renderer);
    textures->v_ennemi = load_image("ressources/enemy.bmp",renderer);
    textures->missile = load_image("ressources/missile.bmp",renderer);
    textures->font = load_font("ressources/arial.ttf",14);
    Changer_taille_image(renderer, &textures->background, textures,SCREEN_WIDTH,SCREEN_HEIGHT);
}

void Changer_taille_image(SDL_Renderer *renderer, SDL_Texture **texture_ptr, textures_t *textures, int longueur, int largeur) {

    SDL_Texture *resized_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, longueur, largeur);
    SDL_SetRenderTarget(renderer, resized_texture);

    // Redimensionne la texture src sur dst
    SDL_RenderCopy(renderer, *texture_ptr, NULL, NULL);
    SDL_SetRenderTarget(renderer, NULL);

    clean_texture(*texture_ptr);
    *texture_ptr = resized_texture;
}

void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}

char* int_to_string (int value) {
    int taille_mini = 20;
    char * str = malloc(sizeof(char)*taille_mini);
    sprintf(str, "%d", value);
    return str;
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {

    if (sprite->is_visible == 1 ) {
        if (sprite->is_alive == 1){
            apply_texture(texture, renderer, sprite->x, sprite->y);
        }
    }
}