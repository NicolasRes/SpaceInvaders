#include "accueil.h"

int Passage_bouton(SDL_EventType event_type, SDL_Event event, int button_x, int button_y, int largeur, int hauteur) {
    int mouseX, mouseY;
    switch (event_type) {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouseX, &mouseY);
            return (mouseX >= button_x && mouseX <= button_x + largeur && mouseY >= button_y && mouseY <= button_y + hauteur);
        default:
            return 0;
    }
}

int Detection_Click_Bouton(int x, int y, int button_x, int button_y, int largeur, int hauteur) {
    return (x >= button_x && x <= button_x + largeur && y >= button_y && y <= button_y + hauteur);
}

SDL_Texture* charger_background(SDL_Renderer *renderer){
    SDL_Texture *background_texture = load_image("ressources/space-background.bmp", renderer);
    if (background_texture == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image de fond : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return background_texture;
}

TTF_Font* charger_police() {
    TTF_Font *font = load_font("ressources/arial.ttf", 24);
    if (font == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la police de caractères : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    return font;
}

void quitter_application(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}


void Creer_Acceuil(SDL_Window *window, SDL_Renderer *renderer) {
    
    SDL_Texture *background_texture =charger_background(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);
    clean_texture(background_texture);
    
    TTF_Font *font = charger_police();
    
    int button_jouer_x = SCREEN_ACC_WIDTH / 2 - 50;
    int button_jouer_y = SCREEN_ACC_HEIGHT / 2 - 50;

    int button_largeur = 100;
    int button_hauteur = 25;
    
    int jouer = 0;
    int quitter = 0;
    SDL_Event event;

    apply_text(renderer, button_jouer_x, button_jouer_y, button_largeur, button_hauteur, "JOUER", font, WHITE);
    apply_text(renderer, button_jouer_x, button_jouer_y + 75, button_largeur, button_hauteur, "QUITTER", font, WHITE);

    update_screen(renderer);

    while (!jouer && !quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter_application(window, renderer);
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                if (Detection_Click_Bouton(x, y, button_jouer_x, button_jouer_y, button_largeur, button_hauteur)) {
                    jouer = 1;
                } else if (Detection_Click_Bouton(x, y, button_jouer_x, button_jouer_y + 75, button_largeur, button_hauteur)) {
                    quitter = 1;
                    quitter_application(window, renderer);
                }
            }
        }

        if (Passage_bouton(SDL_MOUSEMOTION, event, button_jouer_x, button_jouer_y, button_largeur, button_hauteur)) {
            apply_text(renderer, button_jouer_x, button_jouer_y, button_largeur, button_hauteur, "JOUER", font, GREEN);
        } else if (Passage_bouton(SDL_MOUSEMOTION, event, button_jouer_x, button_jouer_y + 75, button_largeur, button_hauteur)) {
            apply_text(renderer, button_jouer_x, button_jouer_y + 75, button_largeur, button_hauteur, "QUITTER", font, GREEN);
        } else {
            apply_text(renderer, button_jouer_x, button_jouer_y, button_largeur, button_hauteur, "JOUER", font, WHITE);
            apply_text(renderer, button_jouer_x, button_jouer_y + 75, button_largeur, button_hauteur, "QUITTER", font, WHITE);
        }

        update_screen(renderer);
        pause(10);
    }

    clean_font(font);

    SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    clear_renderer(renderer);
    update_screen(renderer);
}


