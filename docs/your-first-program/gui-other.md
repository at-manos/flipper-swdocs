---
sidebar_position: 3
---

# GUI

With our model now able to encode the information we need, and the main signature set up, let's start working with the `gui` service.

First, let's start off by including the header, `gui/gui.h`. This will give us easy tools for interfacing with the screen. 

Next, we add a `ViewPort` and a `Gui` object to our `BoxMover` struct. These are the two structures that will allow us to make and draw to a GUI.
```c
#include <furi.h>
#include <gui/gui.h>
#include <stdlib.h>
// -snip-
typedef struct {
    BoxMoverModel* model;

    ViewPort* view_port;
    Gui* gui;

} BoxMover;
```



Let's initialize our new `Gui` and `ViewPort` objects in our `box_mover_alloc` function. 
```c
BoxMover* box_mover_alloc(){
    BoxMover* instance = malloc(sizeof(BoxMover));
    instance->model = malloc(sizeof(BoxMoverModel));
    instance->model->x = 10;
    instance->model->y = 10;


    instance->view_port = view_port_alloc();
    
    instance->gui = furi_record_open("gui");
    gui_add_view_port(instance->gui, instance->view_port, GuiLayerFullScreen);

    return instance;
}
```
We get the `Gui` object by asking furi to open the record with the label "gui", and we use a `gui.h` helper to allocate a `ViewPort`, much like we are making with our `box_mover_alloc`!


In our freeing function, let's disable our ViewPort, close our record, and clean up the memory we've allocated.
```c
void box_mover_free(BoxMover* instance){
    view_port_enabled_set(instance->view_port, false); // Disables our ViewPort
    gui_remove_view_port(instance->gui, view_port); // Removes our ViewPort from the Gui 
    furi_record_close("gui"); // Closes the gui record
    view_port_free(instance->view_port); // Frees memory allocated by view_port_alloc

    free(instance->model);
    free(instance);
}
```


:::info Unsure of your code?
Check out the [code so far](https://github.com/at-manos/flipper-swdocs/tree/main/docs/your-first-program/code-so-far/gui) for this section!
:::