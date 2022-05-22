---
sidebar_position: 5
---

# Main Loop



### Handling Input

With the input callback now processing our new events, we can start utilizing them in our main loop.

Let's do that, and write a simple control flow.


```c
int32_t box_mover_app(void* p){
    // --snip--
    InputEvent event;
    for(bool processing = true; processing;){
        // Pops a message off the queue and stores it in `event`.
        // No message priority denoted by NULL, and 100 ticks of timeout.
        osStatus_t status = osMessageQueueGet(event_queue, &event, NULL, 100); 
        // Acquiring our mutex for this iteration
        GameState* game_state = (GameState*)acquire_mutex_block(&state_mutex) 
  
        // validating input
        if(status==osOK){  
            if(event.type=InputTypePress){
                switch(event.input.key){
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
                        return false;
                        break;
                    case InputKeyBack:
                        return false;
                        break;
                }
            }
        }

        view_port_update(view_port); // signals our draw callback
        release_mutex(&state_mutex, state); // releases our mutex
    }
    // --snip--
    return 0;
}
```