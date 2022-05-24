---
sidebar_position: 5
---

# Callbacks and Concurrency

Currently, our program only does this:

1. Sets up our GameState
2. Allocates a ViewPort
3. Open our gui record
4. Adds the ViewPort to the Gui
5. Creates an input queue
6. Cleans everything up and exits

<br></br>
<p align="center">
No drawing to the screen, and no input processing.
<br></br>

**Let's change that with callbacks!**
</p>

## Callback Methods

The `gui` service provides us with two nice methods for handling drawing and input.

These are aptly declared: `view_port_draw_callback_set` and `view_port_input_callback_set`

Let's look at their full declarations:

```c
void view_port_draw_callback_set(ViewPort* view_port, ViewPortDrawCallback callback, void* context);
void view_port_input_callback_set(ViewPort* view_port, ViewPortInputCallback callback, void* context);
```
As you might guess, `view_port_draw_callback_set` sets the function that is called whenever **a new frame is signalled to be drawn.**
And `view_port_input_callback_set` sets the function that is called whenever **input is recieved**, like a button press.


Conceptually, the callbacks work like this:
- We define a function we want to be called whenever an event occurs
- We use our \*_callback_set functions, and fill it out with the general form:
  - A pointer to our ViewPort instance
  - Our callback function
  - A pointer to the data we want to have access to in our callback functions
    - This is passed to our functions as a void pointer, and we have to cast it back to the type we need.



So, what would we like to do with the callbacks?
- Draw: Draw a box using our GameState's x and y values as an anchor point
- Input: Put key presses onto our input queue
  
Let's tackle the draw callback first.

### Draw Callback

Callbacks pose a problem because they run on a separate thread from our main app. Since we need to access our GameState in the callback, this could result in a [race condition](https://www.techtarget.com/searchstorage/definition/race-condition) between our callbacks and main loop.

Let's fix that by using [mutex](https://en.wikipedia.org/wiki/Lock_\(computer_science\)) to wrap our GameState in a blocking resource, only allowing one thread access at a time.

```c
    // --snip--
int32_t box_mover_app(void* p){
    UNUSED(p);

    GameState* game_state = malloc(sizeof(GameState));
    init_state(game_state);

    ValueMutex state_mutex;
    if(!init_mutex(&state_mutex, game_state, sizeof(GameState))){ // initialize our mutex and checks for error
        free(game_state);
        return -1;
    }

    // --snip--
    return 0;
}
```

Great! Now our GameState can be accessed by multiple threads without having to worry. Let's implement a simple draw callback now.

Our draw callback must conform to the following parameters:
- A pointer to a Canvas
- A pointer to the data we passed in `view_port_draw_callback_set`

```c
// --snip--
void draw_callback(Canvas* canvas, void* ctx){
    GameState* game_state = (GameState*)acquire_mutex((ValueMutex*)ctx, 25) // Acquires mutex with a timeout of 25 ticks.
    if(game_state==NULL){ // If we cannot acquire, exit.
        return;
    }

    canvas_draw_box(canvas, game_state->x, game_state->y, 4, 4); // Draw a box on the screen at game_state->x,y

    release_mutex((ValueMutex*)ctx, game_state); // Release our mutex to be used by other threads.
}
// --snip--
int32_t box_mover_app(void* p){
    // --snip--
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, &state_mutex);

    // --snip--
    return 0;
}
```
:::tip Experiment!
Experiment with other canvas_draw functions like `canvas_draw_str`, `canvas_draw_circle`, and many more! (see `canvas.h`)
:::

Now our `ViewPort` is set up with a drawing callback! Next, we need to implement an input callback.

### Input Callback


Our input callback must conform to the following parameters:
- A pointer to an InputEvent
- A pointer to the data we passed in `view_port_input_callback_set`

The goal for our input callback is pretty simple. All we want it to do is:
- Read an input event
- Place it on the message queue to be read later, in our main loop.

So, let's implement that with `osMessageQueue`.
```c
// --snip--
void input_callback(InputEvent* input, osMessageQueueId_t event_queue){
    // Puts input onto event queue with priority 0, and waits until completion. 
    osMessageQueuePut(event_queue, input, 0, osWaitForever); 
}
// --snip--
int32_t box_mover_app(void* p){
    // --snip--
    
    view_port_input_callback_set(view_port, input_callback, event_queue);

    // --snip--
    return 0;

}

```

Our input callback is now done, and ready for us to read those messages in our main loop.

