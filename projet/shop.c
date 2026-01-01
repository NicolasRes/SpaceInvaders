/* shop.c */
#include "shop.h"

#include <stdio.h>
#include <stdlib.h>

#include "sdl2-light.h"
#include "constantes.h"
#include "etat.h"

// Fonctions privées internes à shop.c (donc pas dans le .h)
// Pas de Javadoc pour l'instant -> elles bougeront dans un futur module UI

static int point_in_rect(int x, int y, const SDL_Rect *r) {
    return (x >= r->x && x <= r->x + r->w && y >= r->y && y <= r->y + r->h);
}

static int mouse_over_rect(const SDL_Rect *r) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    return point_in_rect(mx, my, r);
}

static int max_int(int a, int b) { return (a > b) ? a : b; }

static int cost_ship_speed(const world_t *world) {
    return 10 + 5 * world->ship_speed_bonus;
}

static int cost_missile_speed(const world_t *world) {
    return 10 + 5 * world->missile_speed_bonus;
}

static int cost_fire_rate(const world_t *world) {
    int level = (400 - world->fire_cooldown_ms) / 50;
    if (level < 0) level = 0;
    return 15 + 10 * level;
}

static void purchase_ship_speed(world_t *world) {
    int cost = cost_ship_speed(world);
    if (world->gold >= cost) {
        world->gold -= cost;
        world->ship_speed_bonus += 1;
    }
}

static void purchase_missile_speed(world_t *world) {
    int cost = cost_missile_speed(world);
    if (world->gold >= cost) {
        world->gold -= cost;
        world->missile_speed_bonus += 1;
    }
}

static void purchase_fire_rate(world_t *world) {
    int cost = cost_fire_rate(world);
    if (world->gold >= cost && world->fire_cooldown_ms > 100) {
        world->gold -= cost;
        world->fire_cooldown_ms = max_int(100, world->fire_cooldown_ms - 50);
    }
}

/* Petit panneau semi-transparent */
static void draw_overlay_panel(SDL_Renderer *renderer, SDL_Rect panel) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_RenderFillRect(renderer, &panel);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

/* Rendu texte “bouton” via apply_text (pas de rectangle dessiné) */
static void draw_button(SDL_Renderer *renderer, const SDL_Rect *r, TTF_Font *font, SDL_Color color, const char *label) {
    apply_text(renderer, r->x, r->y, r->w, r->h, (char*)label, font, color);
}

/* --------- API --------- */

void shop_run(SDL_Window *window, SDL_Renderer *renderer, world_t *world, textures_t *textures) {
    (void)window;

    if (!renderer || !world || !textures || !textures->font) {
        /* Si quelque chose manque, on sort proprement du shop */
        world->state = STATE_PLAY;
        return;
    }

    /* Layout */
    SDL_Rect panel;
    panel.w = (int)(SCREEN_WIDTH * 0.75);
    panel.h = (int)(SCREEN_HEIGHT * 0.75);
    panel.x = (SCREEN_WIDTH - panel.w) / 2;
    panel.y = (SCREEN_HEIGHT - panel.h) / 2;

    SDL_Rect btn1 = { panel.x + 40, panel.y + 140, panel.w - 80, 40 };
    SDL_Rect btn2 = { panel.x + 40, panel.y + 200, panel.w - 80, 40 };
    SDL_Rect btn3 = { panel.x + 40, panel.y + 260, panel.w - 80, 40 };
    SDL_Rect btnContinue = { panel.x + 40, panel.y + panel.h - 80, panel.w - 80, 40 };

    SDL_Event event;
    int running = 1;

    /* Petit feedback visuel */
    char feedback[128] = "";
    Uint32 feedback_until = 0;

    while (running && !world->gameover) {

        /* ---------- Events ---------- */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                world->gameover = 1;
                break;
            }

            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode key = event.key.keysym.sym;
                if (key == SDLK_ESCAPE || key == SDLK_RETURN) {
                    running = 0;
                    break;
                }
                if (key == SDLK_1) {
                    int before = world->gold;
                    purchase_ship_speed(world);
                    if (world->gold != before) {
                        snprintf(feedback, sizeof(feedback), "Achat: Vitesse vaisseau +1");
                    } else {
                        snprintf(feedback, sizeof(feedback), "Pas assez de gold.");
                    }
                    feedback_until = SDL_GetTicks() + 1200;
                } else if (key == SDLK_2) {
                    int before = world->gold;
                    purchase_missile_speed(world);
                    if (world->gold != before) {
                        snprintf(feedback, sizeof(feedback), "Achat: Vitesse missile +1");
                    } else {
                        snprintf(feedback, sizeof(feedback), "Pas assez de gold.");
                    }
                    feedback_until = SDL_GetTicks() + 1200;
                } else if (key == SDLK_3) {
                    int before = world->gold;
                    purchase_fire_rate(world);
                    if (world->gold != before) {
                        snprintf(feedback, sizeof(feedback), "Achat: Cadence amelioree");
                    } else {
                        if (world->fire_cooldown_ms <= 100) {
                            snprintf(feedback, sizeof(feedback), "Cadence deja au max.");
                        } else {
                            snprintf(feedback, sizeof(feedback), "Pas assez de gold.");
                        }
                    }
                    feedback_until = SDL_GetTicks() + 1200;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x;
                int my = event.button.y;

                if (point_in_rect(mx, my, &btn1)) {
                    int before = world->gold;
                    purchase_ship_speed(world);
                    if (world->gold != before) snprintf(feedback, sizeof(feedback), "Achat: Vitesse vaisseau +1");
                    else snprintf(feedback, sizeof(feedback), "Pas assez de gold.");
                    feedback_until = SDL_GetTicks() + 1200;
                } else if (point_in_rect(mx, my, &btn2)) {
                    int before = world->gold;
                    purchase_missile_speed(world);
                    if (world->gold != before) snprintf(feedback, sizeof(feedback), "Achat: Vitesse missile +1");
                    else snprintf(feedback, sizeof(feedback), "Pas assez de gold.");
                    feedback_until = SDL_GetTicks() + 1200;
                } else if (point_in_rect(mx, my, &btn3)) {
                    int before = world->gold;
                    purchase_fire_rate(world);
                    if (world->gold != before) snprintf(feedback, sizeof(feedback), "Achat: Cadence amelioree");
                    else {
                        if (world->fire_cooldown_ms <= 100) snprintf(feedback, sizeof(feedback), "Cadence deja au max.");
                        else snprintf(feedback, sizeof(feedback), "Pas assez de gold.");
                    }
                    feedback_until = SDL_GetTicks() + 1200;
                } else if (point_in_rect(mx, my, &btnContinue)) {
                    running = 0;
                    break;
                }
            }
        }

        /* ---------- Render ---------- */
        clear_renderer(renderer);

        /* Fond : réutilise le background du jeu si dispo */
        if (textures->background) {
            apply_texture(textures->background, renderer, 0, 0);
        }

        draw_overlay_panel(renderer, panel);

        /* Titre + infos */
        SDL_Color titleColor = WHITE;
        SDL_Color textColor = WHITE;

        char line[128];
        apply_text(renderer, panel.x + 40, panel.y + 40, panel.w - 80, 40, "SHOP", textures->font, titleColor);

        snprintf(line, sizeof(line), "Gold: %d   |   Vague: %d", world->gold, world->vague);
        apply_text(renderer, panel.x + 40, panel.y + 90, panel.w - 80, 30, line, textures->font, textColor);

        /* Labels boutons (avec coûts) */
        char b1[128], b2[128], b3[160], b4[64];

        snprintf(b1, sizeof(b1), "[1] Vitesse vaisseau +1  (cout: %d)", cost_ship_speed(world));
        snprintf(b2, sizeof(b2), "[2] Vitesse missile +1   (cout: %d)", cost_missile_speed(world));

        if (world->fire_cooldown_ms <= 100) {
            snprintf(b3, sizeof(b3), "[3] Cadence tir (MAX)  (cooldown: %d ms)", world->fire_cooldown_ms);
        } else {
            snprintf(b3, sizeof(b3), "[3] Cadence tir -50ms   (cout: %d)  (cooldown: %d ms)",
                     cost_fire_rate(world), world->fire_cooldown_ms);
        }

        snprintf(b4, sizeof(b4), "CONTINUER (Entree / Ech)");

        SDL_Color c1 = mouse_over_rect(&btn1) ? GREEN : WHITE;
        SDL_Color c2 = mouse_over_rect(&btn2) ? GREEN : WHITE;
        SDL_Color c3 = mouse_over_rect(&btn3) ? GREEN : WHITE;
        SDL_Color c4 = mouse_over_rect(&btnContinue) ? GREEN : WHITE;

        draw_button(renderer, &btn1, textures->font, c1, b1);
        draw_button(renderer, &btn2, textures->font, c2, b2);
        draw_button(renderer, &btn3, textures->font, c3, b3);
        draw_button(renderer, &btnContinue, textures->font, c4, b4);

        /* Affiche les stats actuelles */
        char stats[192];
        snprintf(stats, sizeof(stats),
                 "Bonus: ship_speed=%d  missile_speed=%d  cooldown=%dms",
                 world->ship_speed_bonus, world->missile_speed_bonus, world->fire_cooldown_ms);
        apply_text(renderer, panel.x + 40, panel.y + panel.h - 130, panel.w - 80, 30, stats, textures->font, WHITE);

        /* Feedback achat */
        if (feedback[0] != '\0' && SDL_GetTicks() < feedback_until) {
            apply_text(renderer, panel.x + 40, panel.y + panel.h - 170, panel.w - 80, 30, feedback, textures->font, WHITE);
        }

        update_screen(renderer);
        pause(17);
    }

    /* Sortie shop => on repasse en PLAY (la vague suivante est gérée par main) */
    if (!world->gameover) {
        world->state = STATE_PLAY;
    }
}
