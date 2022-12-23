#include <furi.h> // Core API
#include <furi_hal.h> // Hardware abstraction layer
#include <gui/gui.h> // GUI (screen / keyboard) API
#include <input/input.h> // GUI Input extensions
#include <stdlib.h>


typedef struct {
    int x;
    int y;
} BoxMoverModel;

typedef struct {
    BoxMoverModel* model;
    FuriMutex* model_mutex;

    FuriMessageQueue* event_queue;

    ViewPort* view_port;
    Gui* gui;
} BoxMover;



void draw_callback(Canvas* canvas, void* ctx){
    BoxMover* box_mover = ctx;
    furi_check(furi_mutex_acquire(box_mover->mutex, FuriWaitForever) == FuriStatusOk);

    canvas_draw_box(canvas, box_mover->model->x, box_mover->model->y, 4, 4); // Draw a box on the screen at x,y

    furi_mutex_release(box_mover->model_mutex);
}


void input_callback(InputEvent* input, void* ctx){
    furi_assert(ctx);
    BoxMover* box_mover = ctx;
    // Puts input onto event queue with priority 0, and waits until completion. 
    furi_message_queue_put(box_mover->event_queue, input_event, FuriWaitForever);
}

BoxMover* box_mover_alloc(){
    BoxMover* instance = malloc(sizeof(BoxMover));

    instance->model = malloc(sizeof(BoxMoverModel));
    instance->model->x = 10;
    instance->model->y = 10;

    instance->model_mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    
    instance->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    instance->view_port = view_port_alloc();
    view_port_draw_callback_set(instance->view_port, draw_callback, instance);
    view_port_input_callback_set(instance->view_port, input_callback, instance);

    instance->gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(instance->gui, instance->view_port, GuiLayerFullscreen);

    return instance;
}

void box_mover_free(BoxMover* instance){
    view_port_enabled_set(instance->view_port, false); // Disabsles our ViewPort
    gui_remove_view_port(instance->gui, instance->view_port); // Removes our ViewPort from the Gui 
    furi_record_close(RECORD_GUI); // Closes the gui record
    view_port_free(instance->view_port); // Frees memory allocated by view_port_alloc
    furi_message_queue_free(instance->event_queue);
    
    furi_mutex_free(instance->model_mutex);
    
    free(instance->model);
    free(instance);
}

int32_t box_mover_app(void* p){
    UNUSED(p);

    BoxMover* box_mover = box_mover_alloc();

    InputEvent event;
    for(bool processing = true; processing;){
        // Pops a message off the queue and stores it in `event`.
        furi_check(furi_message_queue_get(box_mover->event_queue, &event, FuriWaitForever) == FuriStatusOk);
        furi_mutex_acquire(box_mover->model_mutex, FuriWaitForever);
        if (event.type == InputTypePress){
            switch (event.key) {
                case InputKeyUp:
                    box_mover->model->y-=2;
                    break;
                case InputKeyDown:
                    box_mover->model->y+=2;
                    break;
                case InputKeyLeft:
                    box_mover->model->x-=2;
                    break;
                case InputKeyRight:
                    box_mover->model->x+=2;
                    break;
                case InputKeyBack:
                    processing = false;
                    break;
                default:
                    break;
            }
        }
        furi_mutex_release(box_mover->model_mutex);
        view_port_update(box_mover->view_port);
    }
    box_mover_free(box_mover);
    return 0;
}