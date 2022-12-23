#include <furi.h> // Core API
#include <furi_hal.h> // Hardware abstraction layer
#include <gui/gui.h> // GUI (screen / keyboard) API
#include <stdlib.h>


typedef struct {
    int x;
    int y;
} BoxMoverModel;

typedef struct {
    BoxMoverModel* model;

    ViewPort* view_port;
    Gui* gui;

} BoxMover;

BoxMover* box_mover_alloc(){
    BoxMover* instance = malloc(sizeof(BoxMover));
    instance->model = malloc(sizeof(BoxMoverModel));
    instance->model->x = 10;
    instance->model->y = 10;


    instance->view_port = view_port_alloc();
    
    instance->gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(instance->gui, instance->view_port, GuiLayerFullscreen);

    return instance;
}

void box_mover_free(BoxMover* instance){
    
    view_port_enabled_set(instance->view_port, false); // Disables our ViewPort
    gui_remove_view_port(instance->gui, instance->view_port); // Removes our ViewPort from the Gui 
    furi_record_close(RECORD_GUI); // Closes the gui record
    view_port_free(instance->view_port); // Frees memory allocated by view_port_alloc

    free(instance->model);
    free(instance);
}

int32_t box_mover_app(void* p){
    UNUSED(p);

    BoxMover* box_mover = box_mover_alloc();

    box_mover_free(box_mover);
    return 0;
}