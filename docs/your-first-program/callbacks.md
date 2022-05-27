---
sidebar_position: 5
---

# Callbacks and Concurrency

Currently, our program only does this:

1. Sets up our BoxMover struct
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
- Draw: Draw a box using our model's x and y values as an anchor point
- Input: Put key presses onto our input queue
  
Let's tackle the draw callback first.

## Tackling Concurrency Issues Using Mutex

Callbacks pose a problem because they run on a separate thread from our main app. Since we need to access our BoxMover in the callback, this could result in a [race condition](https://www.techtarget.com/searchstorage/definition/race-condition) between our callbacks and main loop.

Let's fix that by using [mutex](https://en.wikipedia.org/wiki/Lock_\(computer_science\)) to add a mutex object to our `BoxMover`. This will, in effect, allow it to be used as a blocking resource, only allowing one thread access at a time.


We'll do this by utilizing `osMutex`, an API layer that interfaces with the RTOS kernel. This is best current practice and [deprecates](https://github.com/flipperdevices/flipperzero-firmware/pull/1202#discussion_r867040160) `ValueMutex`, which you may see in some applications.


Let's add an ID to our mutex in our `BoxMover` struct.
```c
typedef struct {
    BoxMoverModel* model;
    osMutexId_t* model_mutex;

    osMessageQueueId_t event_queue;

    ViewPort* view_port;
    Gui* gui;

} BoxMover;
```

Now, let's initialize it in our `box_mover_alloc`, and clean it up in our `box_mover_free`.

```c
BoxMover* box_mover_alloc(){
    // --snip--
    instance->view_port = view_port_alloc();
    
    instance->model_mutex = osMutexNew(NULL);

    instance->gui = furi_record_open("gui");
    // --snip--
}

void box_mover_free(BoxMover* instance){
    // --snip--
    osMessageQueueDelete(instance->event_queue);

    osMutexDelete(instance->model_mutex);
    // --snip--
}
```


Great! Now our `BoxMover` has the ability to be modified without the possibility of inducing a race condition. Let's implement those callbacks now.

## Draw Callback

Our draw callback must conform to the following parameters:
- A pointer to a Canvas
- A pointer to the data we pass in `view_port_draw_callback_set` 

(For both callbacks, we will be passing in an instance of `BoxMover`.)

```c
// --snip--
void draw_callback(Canvas* canvas, void* ctx){
    BoxMover* box_mover = ctx;
    furi_check(osMutexAcquire(box_mover->model_mutex, osWaitForever)==osOK);

    canvas_draw_box(canvas, box_mover->model->x, box_mover->model->y, 4, 4); // Draw a box on the screen

    osReleaseMutex(box_mover->model_mutex);
}
```
Here, we try to acquire our mutex for however long it takes (denoted by osWaitForever), and is wrapped in a `furi_check`, which will crash the program if there is an error with the mutex.

Once we have it, we know that only this thread has the mutex. Great! We can start using the variables now. 

We draw a simple box at x,y and with a height and width of 4, and then release the mutex to be used by another thread.

:::tip Experiment!
Experiment with other canvas_draw functions like `canvas_draw_str`, `canvas_draw_circle`, and many more! (see `canvas.h`)
:::

Let's add it to our `ViewPort` in our `box_mover_alloc` function:

```c
BoxMover* box_mover_alloc(){
    // --snip-- 

    instance->view_port = view_port_alloc();
    view_port_draw_callback_set(instance->view_port, draw_callback, instance);
    
    instance->model_mutex = osMutexNew(NULL);
    // --snip-- 
}
```

Now our `ViewPort` is set up with a drawing callback! Next, we need to implement an input callback.



## Input Callback


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
    BoxMover* box_mover = ctx;
    // Puts input onto event queue with priority 0, and waits until completion. 
    osMessageQueuePut(box_mover->event_queue, input, 0, osWaitForever); 
}
BoxMover* box_mover_alloc(){
    // --snip--
    view_port_draw_callback_set(instance->view_port, draw_callback, instance);

    view_port_input_callback_set(instance->view_port, input_callback, instance);
    // --snip--
}

```

Our input callback is now done, and ready for us to read those messages in our main loop.

:::info Unsure of your code?
Check out the [code so far](https://github.com/at-manos/flipper-swdocs/tree/main/docs/your-first-program/code-so-far/callbacks) for this section!
:::