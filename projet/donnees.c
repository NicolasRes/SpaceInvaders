#include"donnees.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>



int generate_number (int a,int b ) {
    return rand ()%( b-a)+a ;
}

void init_sprite (sprite_t * sprite, int x, int y, int w, int h, int v, int alv) {
    sprite->x = x;
    sprite->y = y;
    sprite->w = w; //largeur sprite
    sprite->h = h; //hauteur sprite
    sprite->v = v; //vitesse sprite
    sprite->is_visible = 1;
    sprite->is_alive=alv;
}

void init_enemies(world_t *world){
   
    world->enemies=malloc(NB_ENEMIES*sizeof(sprite_t*));
    for(int i=0;i<NB_ENEMIES;i++){
        world->enemies[i]= malloc(sizeof(sprite_t));
    }
    for (int i=0;i<NB_ENEMIES;i++){
        init_sprite(world->enemies[i],generate_number(0,SCREEN_WIDTH-SHIP_SIZE),-SHIP_SIZE/2 - i * VERTICAL_DIST,SHIP_SIZE,SHIP_SIZE,ENEMY_SPEED,1);
    }
    
}

void set_visible (sprite_t * sprite) {
    sprite->is_visible = 1;
}

void set_invisible (sprite_t * sprite) {
    sprite->is_visible = 0;
}

void print_sprite (sprite_t * sprite) {
    printf("Coordonnée x : %d\n", sprite->x);
    printf("Coordonnée y : %d\n", sprite->y);
    printf("Hauteur : %d\n", sprite->h);
    printf("Largeur : %d\n", sprite->w);
    printf("Vitesse : %d\n", sprite->v);
    printf("en vie :%d\n ", sprite->is_alive);
}

void init_data(world_t * world){
    world->vaisseau = malloc(sizeof(sprite_t));
    world->missile = malloc(sizeof(sprite_t));
    world->nb_v_out = 0;
    world->score = 0;


    init_sprite (world->vaisseau, (SCREEN_WIDTH/2) - (SHIP_SIZE/2), SCREEN_HEIGHT- (SHIP_SIZE*3/2), SHIP_SIZE, SHIP_SIZE, world->vaisseau->v = VAISSEAU_SPEED,1);
    print_sprite(world->vaisseau);
    
    //init_sprite (world->v_ennemi, (SCREEN_WIDTH/2) - (SHIP_SIZE/2), (SHIP_SIZE/2), SHIP_SIZE, SHIP_SIZE, ENEMY_SPEED,1);
   

    init_sprite (world->missile, world->vaisseau->x + (SHIP_SIZE/2) - (MISSILE_SIZE/2), world->vaisseau->y - (MISSILE_SIZE), SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED,0);

    init_enemies(world);


    set_invisible(world->missile);
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->win=0;
    
}

void clean_data(world_t *world){
    free(world->vaisseau);
    //free(world->v_ennemi);
    free(world->missile);
    for (int i=0;i<NB_ENEMIES;i++){
        (world->enemies[i]);
    }
    free(world->enemies);
}



int is_game_over(world_t *world){
    return world->gameover;
}

void limite_ecran_joueur(world_t *world){

    // Limite gauche
    if (world->vaisseau->x < 0) {
        world->vaisseau->x = 0;
    }
    
    // Limite droite
    if (world->vaisseau->x + world->vaisseau->w > SCREEN_WIDTH) {
        world->vaisseau->x = SCREEN_WIDTH - world->vaisseau->w;
    }
}


void limite_ecran_ennemi(world_t *world){

    // Limite basse

    for (int i = 0; i < NB_ENEMIES; i++) {
         if (world->enemies[i]->y > SCREEN_HEIGHT) {
            if (world->enemies[i]->is_alive == 1) {
                world->enemies[i]->is_alive = 0;
                world->nb_v_out += 1;
            }
        }
    }
}

void limite_ecran_missile(world_t * world){

    //Limite gauche
    if (world->missile->y < 0) {
        world->missile->is_alive= 0;
        world->missile->is_visible= 0;
    }
}


int sprites_collide_rectangle(sprite_t *sp1, sprite_t *sp2) {
    
    float sp1_gauche = sp1->x;
    float sp1_droite = sp1->x + sp1->w;
    float sp1_haut = sp1->y;
    float sp1_bas = sp1->y + sp1->h;

    float sp2_gauche = sp2->x;
    float sp2_droite = sp2->x + sp2->w;
    float sp2_haut = sp2->y;
    float sp2_bas = sp2->y + sp2->h;

    // chevauchement
    if (sp1_droite >= sp2_gauche && sp1_gauche <= sp2_droite && sp1_bas >= sp2_haut && sp1_haut <= sp2_bas) {
        
        return 1;
    } 
    return 0;
    
}

int sprites_collide_cercle(sprite_t *sp1, sprite_t *sp2) {
    
    if (sp1->is_alive && sp2->is_alive){
        // Calcul des coordonnées des centres des sprites
        float sp1_centre_x = sp1->x + sp1->w / 2.0;
        float sp1_centre_y = sp1->y + sp1->h / 2.0;
        float sp2_centre_x = sp2->x + sp2->w / 2.0;
        float sp2_centre_y = sp2->y + sp2->h / 2.0;

        // Calcul de la distance entre les centres des sprites
        float distance_centres = sqrt(pow(sp2_centre_x - sp1_centre_x, 2) + pow(sp2_centre_y - sp1_centre_y, 2));
        
        // Si distance entre les centres est <= somme des rayons alors chevauchement
        float rayon_sp1 = sp1->w / 2.0;
        float rayon_sp2 = sp2->w / 2.0;
        if (distance_centres <= rayon_sp1 + rayon_sp2) {
            printf("collision\n");
            return 1; 
        } 
    }
    
    return 0;
}
 

void handle_sprites_collision_vaisseau(sprite_t *sp1, sprite_t *sp2) {
    // Vérifier si les deux sprites sont encore visibles, en vie et en collision
    if (sp1->is_visible && sp1->is_alive && sp2->is_visible && sp2->is_alive && sprites_collide_cercle(sp1, sp2)) {
        sp1->is_alive = 0;
        sp2->is_alive = 0;

    }
    
}

void handle_sprites_collision_missile(sprite_t *sp1, sprite_t *sp2,world_t *world) {
    // Vérifier si les deux sprites sont encore visibles, en vie et en collision
    if (sp1->is_visible && sp1->is_alive && sp2->is_visible && sp2->is_alive && sprites_collide_cercle(sp1, sp2)) {
        sp1->is_alive = 0;
        sp2->is_alive = 0;
        set_invisible(sp1);
        sp1->is_alive=0;
        world->score+=1;
    }
    
}

void update_enemies(world_t *world){
    for(int i=0;i<NB_ENEMIES;i++){
        world->enemies[i]->y +=world->enemies[i]->v;
    }
}

void afficher_score_pendantPartie(world_t * world,int vout,int score){

    if (world->nb_v_out!= vout || world->score!= score ){
        printf("V out :%d\n", world->nb_v_out);
        printf("Score :%d\n\n", world->score);
    } 
}

void MessageVictoire(world_t * world){

    if (world->win==1){

        printf("Vous avez abattu tous les ennemis, vous avez gagnez!\n");
        printf("Votre Score est mutiplié par 2, score : %d\n", world->score);

    }else{
        printf("Un ennemi vous a abattu, Score: %d\n",world->score);
    } 
    

}

void compute_game(world_t *world){

    if (world->vaisseau->is_alive == 0){
            
        world->gameover=1;
        
    } 

    if(world->nb_v_out + world->score == NB_ENEMIES ){
        if(world->score==NB_ENEMIES){
            world->score *=2;
            world->win=1;
            world->gameover =1;
            
        }else{
            world->score =0;
            world->gameover =1;
        }
            
    } 
    
}


void update_data(world_t *world){
    
    update_enemies(world);
    if(world->missile->is_visible == 1) {
        world->missile->y -= world->missile->v;
    }

    int ancien_score_vaisseau= world->nb_v_out;
    int ancien_score_joueur=world->score;

    limite_ecran_joueur(world);
    limite_ecran_ennemi(world);
    limite_ecran_missile(world);

    for (int i = 0; i < NB_ENEMIES; i++) {
        handle_sprites_collision_vaisseau(world->vaisseau,world->enemies[i]);
        handle_sprites_collision_missile(world->missile,world->enemies[i],world);

        compute_game(world);
        
    }

    afficher_score_pendantPartie(world,ancien_score_vaisseau,ancien_score_joueur);
}



void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }

        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_KEYDOWN ) {
            if(event->key.keysym.sym == SDLK_ESCAPE){
                //si la touche appuyée est 'ESCAPE'
                world->gameover = 1;
            }
        }

        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'D'
            if(event->key.keysym.sym == SDLK_d){
                world->vaisseau->x += world->vaisseau->v;
            }
        }

        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'G'
            if(event->key.keysym.sym == SDLK_q){
                world->vaisseau->x -= world->vaisseau->v;
            }
        }

         // Si la touche appuyée est 'ESPACE' et que le vaisseau est visible
        if (event->key.keysym.sym == SDLK_SPACE && world->vaisseau->is_visible && world->vaisseau->is_alive && world->missile->is_alive==0 &&  world->missile->is_visible==0){
            world->missile->x = world->vaisseau->x + SHIP_SIZE/2 - MISSILE_SIZE/2;
            world->missile->y = world->vaisseau->y - MISSILE_SIZE;
            world->missile->is_visible = 1;
            world->missile->is_alive=1;
        }
    }
}