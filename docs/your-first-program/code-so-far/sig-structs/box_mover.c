#include <furi.h> // Core API
#include <furi_hal.h> // Hardware abstraction layer
#include <stdlib.h>


typedef struct {
    int x;
    int y;
} BoxMoverModel;

typedef struct {
    BoxMoverModel* model;
} BoxMover;

BoxMover* box_mover_alloc(){
    BoxMover* instance = malloc(sizeof(BoxMover));
    instance->model = malloc(sizeof(BoxMoverModel));
    instance->model->x = 10;
    instance->model->y = 10;
    
    return instance;
}

void box_mover_free(BoxMover* instance){
    free(instance->model);
    free(instance);
}

int32_t box_mover_app(void* p){
    UNUSED(p);

    BoxMover* box_mover = box_mover_alloc();


    box_mover_free(box_mover);
    return 0;
}