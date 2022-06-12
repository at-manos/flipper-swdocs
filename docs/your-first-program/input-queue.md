---
sidebar_position: 4
---

# Input Queue

In order to take in input, we're going to be utilizing `osMessageQueue`, which, as the name implies, allows us to create queues of messages.

For our `BoxMover` struct, all we need to do is declare an `osMessageQueueId_t`, which will be an ID for our queue, so we can reference it later.
```c
typedef struct {
    BoxMoverModel* model;

    osMessageQueueId_t event_queue;

    ViewPort* view_port;
    Gui* gui;

} BoxMover;
```

Now, let's actually create a queue inside of our `box_mover_alloc` function.

```c
BoxMover* box_mover_alloc(){
    // --snip--
    instance->gui = furi_record_open("gui");

    instance->event_queue = osMessageQueueNew(8, sizeof(InputEvent), NULL);
    
    return instance;
}
```
The above code creates a new event queue that will hold `InputEvent`s (from the `input` service).

In its parameters, we define that it will have:
- A maximum of 8 messages in the queue
- A message size of an InputEvent
- Default attributes (specified by NULL)

Let's remember to free this new input queue in `box_mover_free`:

```c
void box_mover_free(BoxMover* instance){
    // --snip--
    osMessageQueueDelete(instance->event_queue);

    free(instance->model);
    free(instance);
}
```

:::info Unsure of your code?
Check out the [code so far](https://github.com/at-manos/flipper-swdocs/tree/main/docs/your-first-program/code-so-far/input-queue) for this section!
:::