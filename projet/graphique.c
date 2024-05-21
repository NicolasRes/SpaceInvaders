#include "graphique.h"


void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->player);
    clean_texture(textures->v_ennemi);
    clean_texture(textures->missile);
    clean_font(textures->font);
}

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->player = load_image("ressources/spaceship.bmp",renderer);
    textures->background = load_image("ressources/space-background.bmp",renderer);
    textures->v_ennemi = load_image("ressources/enemy.bmp",renderer);
    textures->missile = load_image("ressources/missile.bmp",renderer);
    textures->font=load_font("ressources/arial.ttf",14);
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

void AffichageValeur(SDL_Renderer *renderer, world_t *world,textures_t *textures,SDL_Color color,char * score_str,char * vague_str,char * gold_str){

    //afficher valeur vague,score et gold
    apply_text(renderer,10,10,6*14,50, "Vague ",textures->font,color);
    apply_text(renderer,100,10,25,50, vague_str,textures->font,color);
    apply_text(renderer,10,60,6*14,50, "Score: ",textures->font,color);
    apply_text(renderer,100,60,25,50, score_str,textures->font,color);
    apply_text(renderer,SCREEN_WIDTH - 10*14,60,6*14,50, "Gold: ",textures->font,color);
    apply_text(renderer,SCREEN_WIDTH - 4*14,60,50,50, gold_str,textures->font,color);
}

void AffichageEntreVague(SDL_Renderer *renderer, world_t *world,textures_t *textures,char * vague_str){

    if (world->attente==1){
        world->attente=0;
        
        apply_text(renderer, SCREEN_WIDTH / 2 - ((5 * 25) / 2), SCREEN_HEIGHT / 2 - 50, 5 * 25, 100, "Vague ", textures->font, WHITE);   
        apply_text(renderer, SCREEN_WIDTH / 2 + ((5 * 25) / 2) + 10, SCREEN_HEIGHT / 2 - 50, 25, 100, vague_str, textures->font, WHITE);

        update_screen(renderer);
        pause(1000);
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //Mise à jour affichage valeur su l'ecran
    char * score_str = int_to_string(world->score);
    char * vague_str = int_to_string(world->vague);
    char * gold_str = int_to_string(world->gold);

    //magenta
    SDL_Color color ={255,0,255};

    clear_renderer(renderer);
    
    //afficher textures
    apply_background(renderer, textures);
    apply_sprite(renderer, textures->player, world->vaisseau);
    apply_enemies(renderer,world,textures);
    apply_sprite(renderer, textures->missile, world->missile);
    
    // afficher Valeur utiles
    AffichageValeur(renderer,world,textures,color,score_str,vague_str,gold_str);

    //afficher numéro de la nouvelle vague
    AffichageEntreVague(renderer,world,textures,vague_str);
    // mise à jour ecrant     
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


void GameOver(SDL_Renderer *renderer, world_t *world, textures_t *textures) {

    // récup taille qui faut
    int text_width, text_height;
    TTF_SizeText(textures->font, "GAME OVER", &text_width, &text_height);

    // afficher en plus grand
    text_width*= 3   ;
    text_height*= 3  ;


    int text_x = (SCREEN_WIDTH - text_width) / 2;
    int text_y = (SCREEN_HEIGHT - text_height) / 2;

    apply_text(renderer, text_x, text_y, text_width, text_height, "GAME OVER", textures->font, WHITE);
    update_screen(renderer);
}