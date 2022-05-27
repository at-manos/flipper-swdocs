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

void draw_callback(Canvas* canvas, void* ctx){
    GameState* game_state = (GameState*)acquire_mutex((ValueMutex*)ctx, 25); // Acquires mutex with a timeout of 25 ticks.
    if(game_state==NULL){ // If we cannot acquire, exit.
        return;
    }

    canvas_draw_box(canvas, game_state->x, game_state->y, 4, 4); // Draw a box on the screen at game_state->x,y

    release_mutex((ValueMutex*)ctx, game_state); // Release our mutex to be used by other threads.
}


void input_callback(InputEvent* input, osMessageQueueId_t event_queue){
    // Puts input onto event queue with priority 0, and waits until completion. 
    osMessageQueuePut(event_queue, input, 0, osWaitForever); 
}

int32_t box_mover_app(void* p){
    UNUSED(p);
    osMessageQueueId_t event_queue = osMessageQueueNew(8, sizeof(InputEvent), NULL);

    GameState* game_state = malloc(sizeof(GameState));
    init_state(game_state);

    ValueMutex state_mutex;
    if(!init_mutex(&state_mutex, game_state, sizeof(GameState))){ // initialize our mutex and checks for error
        free(game_state);
        return -1;
    }

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, &state_mutex);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    Gui* gui = furi_record_open("gui");
    gui_add_view_port(gui, view_port, GuiLayerFullScreen);

    InputEvent event;
    for(bool processing = true; processing;){
        // Pops a message off the queue and stores it in `event`.
        // No message priority denoted by NULL, and 100 ticks of timeout.
        osStatus_t status = osMessageQueueGet(event_queue, &event, NULL, 100); 
        // Acquiring our mutex for this iteration
        GameState* game_state = (GameState*)acquire_mutex_block(&state_mutex) 
  
        // validating input
        if(status==osOK){  
            if(event.type==InputTypePress){
                switch(event.key){
                    case InputKeyUp:
                        game_state->y-=2;
                        break;
                    case InputKeyDown:
                        game_state->y+=2;
                        break;
                    case InputKeyLeft:
                        game_state->x-=2;
                        break;
                    case InputKeyRight:
                        game_state->x+=2;
                        break;
                    case InputKeyOk:
                    case InputKeyBack:
                        processing = false;
                        break;
                }
            }
        }
        view_port_update(view_port); // signals our draw callback
        release_mutex(&state_mutex, game_state); // releases our mutex
    }

    view_port_enabled_set(view_port, false); // Disables our ViewPort
    gui_remove_view_port(gui, view_port); // Removes our ViewPort from the Gui 
    furi_record_close("gui"); // Closes the gui record
    view_port_free(view_port); // Frees memory allocated by view_port_alloc
    osMessageQueueDelete(event_queue);
    return 0;
}