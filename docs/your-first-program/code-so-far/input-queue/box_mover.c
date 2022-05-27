#include <furi.h>
#include <gui/gui.h>
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
    osMessageQueueId_t event_queue = osMessageQueueNew(8, sizeof(InputEvent), NULL);

    GameState* game_state = malloc(sizeof(GameState));
    init_state(game_state);

    ViewPort* view_port = view_port_alloc();

    Gui* gui = furi_record_open("gui");
    gui_add_view_port(gui, view_port, GuiLayerFullScreen);


    view_port_enabled_set(view_port, false); // Disables our ViewPort
    gui_remove_view_port(gui, view_port); // Removes our ViewPort from the Gui 
    furi_record_close("gui"); // Closes the gui record
    view_port_free(view_port); // Frees memory allocated by view_port_alloc
    osMessageQueueDelete(event_queue);
    return 0;
}