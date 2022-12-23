---
sidebar_position: 5
---

# Main Loop



### Handling Input

With the input callback now processing our new events, we can start utilizing them in our main loop.

Let's do that, and write a simple control flow.


```c
int32_t box_mover_app(void* p){
    UNUSED(p);

    BoxMover* box_mover = box_mover_alloc();

    InputEvent event;
    for(bool processing = true; processing;){
        // Pops a message off the queue and stores it in `event`.
        furi_check(furi_message_queue_get(box_mover->event_queue, &event, FuriWaitForever) == FuriStatusOk);
        furi_mutex_acquire(box_mover->model_mutex, FuriWaitForever);
        if(event.type==InputTypePress){
            switch(event.key){
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
        view_port_update(box_mover->view_port); // signals our draw callback
    } 
    box_mover_free(box_mover);
    return 0;
}
```

As you can see, because of our struct-oriented approach, this makes our final client calls much easier, and these skills and structure will transfer very well to other [GUI Paradigms](/docs/category/gui-paradigms).

:::info Unsure of your code?
Check out the [code so far](https://github.com/at-manos/flipper-swdocs/tree/main/docs/your-first-program/code-so-far/main-loop) for this section!
:::