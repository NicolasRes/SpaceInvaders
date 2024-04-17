#include "graphique.h"


void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->player);
    clean_texture(textures->v_ennemi);
    clean_texture(textures->missile);
    clean_font(textures->font);
}

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->player = load_image("ressources/vaisseau-spatial.bmp",renderer);
    textures->background = load_image("ressources/space-background.bmp",renderer);
    textures->v_ennemi = load_image("ressources/enemy.bmp",renderer);
    textures->missile = load_image("ressources/missile.bmp",renderer);
    textures->font=load_font("ressources/arial.ttf",14);
    Changer_taille_image(renderer, &textures->background, textures,SCREEN_WIDTH,SCREEN_HEIGHT);
    Changer_taille_image(renderer, &textures->player, textures,SHIP_SIZE,SHIP_SIZE);
    
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

void apply_enemies(SDL_Renderer *renderer,world_t * world,textures_t *textures){
    for (int i=0;i<world->nb_enemies_current;i++){
        apply_sprite(renderer,textures->v_ennemi,world->enemies[i]);
    }
    
}

char* int_to_string (int value) {
    int taille_mini = 20;
    char * str = malloc(sizeof(char)*taille_mini);
    sprintf(str, "%d", value);
    return str;
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    char * score_str = int_to_string(world->score);
    char * vague_str = int_to_string(world->vague);

    clear_renderer(renderer);
    
    apply_background(renderer, textures);

    apply_sprite(renderer, textures->player, world->vaisseau);
    
    apply_enemies(renderer,world,textures);

    apply_sprite(renderer, textures->missile, world->missile);
    
    SDL_Color color = { 255, 0, 255 };

    
    apply_text(renderer,10,10,6*14,50, "Vague: ",textures->font,color);
    apply_text(renderer,100,10,25,50, vague_str,textures->font,color);

    apply_text(renderer,10,60,6*14,50, "Score: ",textures->font,color);
    apply_text(renderer,100,60,25,50, score_str,textures->font,color);
    
    if (world->attente==1){
        world->attente=0;
        
        apply_text(renderer, SCREEN_WIDTH / 2 - ((5 * 25) / 2), SCREEN_HEIGHT / 2 - 50, 5 * 25, 100, "Vague : ", textures->font, WHITE);   
        apply_text(renderer, SCREEN_WIDTH / 2 + ((5 * 25) / 2) + 10, SCREEN_HEIGHT / 2 - 50, 25, 100, vague_str, textures->font, WHITE);

        update_screen(renderer);
        pause(1000);
    }
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
    init_sdl(window,renderer,SCREEN_ACC_WIDTH, SCREEN_ACC_HEIGHT);
    init_ttf();
    Creer_Acceuil(*window, *renderer);
    init_data(world);
    init_textures(*renderer,textures);
}