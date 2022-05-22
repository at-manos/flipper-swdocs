---
sidebar_position: 3
---

# GUI

With our game state now able to encode the information we need, and the main signature set up, let's start working with the `gui` service.

First, let's start off by including the header, `gui/gui.h`. This will give us easy tools for interfacing with the screen. 
```c
#include <gui/gui.h>
// -snip-
int32_t box_mover_app(void* p){
    // --snip--
    ViewPort* view_port = view_port_alloc() // Gives us a pointer to a ViewPort instance

    return 0;
}
```

Next, we'll get our `Gui` instance by asking furi to open the record. 

We can add our newly created `ViewPort` to it.
```c
    int32_t box_mover_app(void* p){
        // --snip--
        ViewPort* view_port = view_port_alloc() // Gives us a pointer to a ViewPort instance

        Gui* gui = furi_record_open("gui") // Gives us a pointer to our Gui.
        gui_add_view_port(gui, view_port, GuiLayerFullScreen) // Adds our ViewPort to the Gui in full screen.
        
        return 0;
    }
```

Let's disable our ViewPort, close our record, and clean up the memory we've allocated.
```c
    #include <furi.h>
    #include <gui/gui.h>
    // --snip--
    
    int32_t box_mover_app(void* p){
        // --snip--

        view_port_enabled_set(view_port, false); // Disables our ViewPort
        gui_remove_view_port(gui, view_port); // Removes our ViewPort from the Gui 
        furi_record_close("gui"); // Closes the gui record
        view_port_free(view_port); // Frees memory allocated by view_port_alloc
        return 0;
    }
```


