#include <furi.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} GameState;

void init_state(GameState* game_state){
    game_state->x = 10;
    game_state->y = 10;
}

int32_t box_mover_app(void* p){
    UNUSED(p);

    GameState* game_state = malloc(sizeof(GameState));
    init_state(game_state);

    return 0;
}