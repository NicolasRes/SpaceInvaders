#include"donnees.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


///// Fonctions internes /////

static void limite_ecran_joueur(world_t *world){
    // Limite gauche
    if (world->vaisseau->x < 0) {
        world->vaisseau->x = 0;
    }
    // Limite droite
    if (world->vaisseau->x + world->vaisseau->w > SCREEN_WIDTH) {
        world->vaisseau->x = SCREEN_WIDTH - world->vaisseau->w;
    }
}

static void limite_ecran_ennemi(world_t *world){
    // Limite basse
    for (int i = 0; i < world->nb_enemies_current; i++) {
         if (world->enemies[i]->y > SCREEN_HEIGHT) {
            if (world->enemies[i]->is_alive == 1) {
                world->enemies[i]->is_alive = 0;
                world->nb_v_out += 1;
            }
        }
    }
}

static void limite_ecran_missiles(world_t * world){

    // Limite haute
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (world->missiles[i].is_visible && world->missiles[i].y < 0) {
            world->missiles[i].is_alive = 0;
            world->missiles[i].is_visible = 0;
        }
    }
}

static void free_enemies(world_t *world) {
    for (int i=0; i<world->nb_enemies_current; i++){
        free((world->enemies[i]));
    }
    free(world->enemies);
    world->enemies = NULL;
}

static sprite_t* get_free_missile(world_t *world){
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (world->missiles[i].is_alive == 0 && world->missiles[i].is_visible == 0) {
            return &world->missiles[i];
        }
    }
    return NULL;
}

///// Fonctions globales /////

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

void init_enemies(world_t *world) {
    world->enemies = malloc(world->nb_enemies_current * sizeof(sprite_t*));
    for(int i = 0; i < world->nb_enemies_current; i++) {
        world->enemies[i] = malloc(sizeof(sprite_t)); 
        //ajout -20 en y sinon apparait pendant ecran entre vague
        init_sprite(world->enemies[i], generate_number(0, SCREEN_WIDTH - SHIP_SIZE), -SHIP_SIZE / 2 - i * VERTICAL_DIST -50, SHIP_SIZE, SHIP_SIZE, world->vitesse_enemies, 1);
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

void init_world(world_t* world){
    world->nb_v_out = 0;
    world->score = 0;
    world->gold = 0;
    world->gameover = 0;
    world->win=0;
    world->vague=1;
    world->nb_enemies_current = NB_ENEMIES;
    world->vitesse_enemies= ENEMY_SPEED;
    world->score_manche=0;
    world->state = STATE_MENU;
    world->dmg = 1;
    world->fire_cooldown_ms = 400;          // délai min entre tirs
    world->missile_speed_bonus = 0;
    world->ship_speed_bonus = 0;

    world->max_hp = 1;
    world->hp = world->max_hp;

    world->last_shot_ticks = 0;
}

void init_data(world_t * world){
    world->vaisseau = malloc(sizeof(sprite_t));

    init_world(world);

    // init joueur
    init_sprite (world->vaisseau, 
        (SCREEN_WIDTH/2) - (SHIP_SIZE/2), 
        SCREEN_HEIGHT - (SHIP_SIZE*3/2), 
        SHIP_SIZE, SHIP_SIZE, 
        VAISSEAU_SPEED, 1);

    // init missile
    for(int i = 0; i < MAX_MISSILES; i++) {
        init_sprite (&world->missiles[i], 
            0, 0, 
            MISSILE_SIZE, MISSILE_SIZE, 
            MISSILE_SPEED, 0);

        set_invisible(&world->missiles[i]);
        world->missiles[i].is_alive = 0;
    }

    init_enemies(world);
}

void clean_data(world_t *world){
    free(world->vaisseau);
    free_enemies(world);
}

int is_game_over(world_t *world){
    return world->gameover;
}

int sprites_collide_rectangle(sprite_t *sp1, sprite_t *sp2) {

    // Coordonnées des côtés des rectangles
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

void handle_missile_collision(world_t *world) {
    // On boucle tant sur tous les missiles
    for (int m = 0; m < MAX_MISSILES; m++) {
        sprite_t *missile = &world->missiles[m];

        // Si le missile est en vie, on ignore
        if (!missile->is_alive) continue;

        // On boucle sur les ennemis en vie
        for (int e = 0; e < world->nb_enemies_current; e++) {
            sprite_t *enemy = world->enemies[e];
            
            // Si l'ennemi n'est pas en vie, on ignore
            if (!enemy->is_alive) continue;

            // En cas de collision entre un missile et un ennemi, le missile et l'ennemi disparaissent
            if (sprites_collide_cercle(missile, enemy)) {
                missile->is_alive = 0;
                missile->is_visible = 0;
                enemy->is_alive = 0;

                // On gère aussi le score et l'argent gagné
                world->score++;
                world->gold += rand() % 9 + 1;
                world->score_manche++;
                break; // un missile touche un seul ennemi
            }
        }
    }
}

void update_enemies(world_t *world){
    for(int i=0;i<world->nb_enemies_current;i++){
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
    printf("Un ennemi vous a abattu ! Score final: %d\n",world->score);    
}

void Verif_Gameover(world_t *world) {
    if (world->vaisseau->is_alive == 0) {
        world->gameover = 1;
    } 
}

void Verif_TousAbattus(world_t *world){

    if (world->nb_v_out==0){
        printf("Vous avez abattu tous les ennemies !\n");
        printf("Score Multiple par 2!!\n");
        world->score*=2;
    }
}

void MiseAJour_Vague(world_t *world){
    world->vague += 1;
    world->nb_v_out = 0;
    world->nb_enemies_current += 2;
    world->score_manche = 0;
    world->vitesse_enemies += 1;
    world->vaisseau->v+=1;
}


void Verif_FinDevague(world_t *world) {
    if (world->nb_v_out + world->score_manche == world->nb_enemies_current) {
        Verif_TousAbattus(world);
        world->attente = 1;
        world->state = STATE_SHOP;
    }
}

void compute_game(world_t *world) {
    Verif_Gameover(world);
    Verif_FinDevague(world);  
}

void update_missiles(world_t *world){
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (world->missiles[i].is_visible) {
            int speed = world->missiles[i].v + world->missile_speed_bonus;
            world->missiles[i].y -= speed;
        }
    }
}

void Verif_Collision(world_t *world){
    for (int i = 0; i < world->nb_enemies_current; i++) {
        handle_sprites_collision_vaisseau(world->vaisseau, world->enemies[i]);
    }
    handle_missile_collision(world);
    compute_game(world); 
}

void update_data(world_t *world){
    //faire avancer enemies
    update_enemies(world);

    //faire avancer missile
    update_missiles(world);
    
    //Vérification limite sprites
    limite_ecran_joueur(world);
    limite_ecran_ennemi(world);
    limite_ecran_missiles(world);

    Verif_Collision(world);
    
}


void handle_events(SDL_Event *event, world_t *world) {
    const Uint8 *keystates;
    keystates = SDL_GetKeyboardState(NULL);
    Uint32 now = SDL_GetTicks();    // Nb de ms depuis l'initialisation de la librairie SDL
        
    //déplacement vers droite
    if (keystates[SDL_SCANCODE_D]) {
        world->vaisseau->x += world->vaisseau->v + world->ship_speed_bonus;
    }
    //déplacement vers gauche
    if (keystates[SDL_SCANCODE_Q]) {
        world->vaisseau->x -= world->vaisseau->v + world->ship_speed_bonus;
    }

    // Le missile dépend du cooldown, on n'a plus à attendre que l'ancien missile sorte de l'écran ou touche une cible pour tirer à nouveau
    // Un seul missile à la fois pour le moment
    if (keystates[SDL_SCANCODE_SPACE] &&
        world->vaisseau->is_visible &&
        world->vaisseau->is_alive &&
        (now - world->last_shot_ticks >= (Uint32)world->fire_cooldown_ms)) {
        
        sprite_t *m = get_free_missile(world);

        // Spawn missile
        if(m) {
            world->last_shot_ticks = now;
            m->x = world->vaisseau->x + SHIP_SIZE/2 - MISSILE_SIZE/2;
            m->y = world->vaisseau->y - MISSILE_SIZE;
            m->is_visible = 1;
            m->is_alive = 1;
        }
    }

    // vérification si quitte (croix rouge)
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) { 
            world->gameover = 1;
        }
    }
}