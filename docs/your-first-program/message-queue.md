---
sidebar_position: 4
---

# Input Queue

In order to take in input, we're going to be utilizing `osMessageQueue`, which, as the name implies, allows us to create queues of messages.

```c
#include <input/input.h>
#include <stdlib.h>
// --snip--
int32_t box_mover_app(void* p){
    osMessageQueueId_t event_queue = osMessageQueueNew(8, sizeof(InputEvent), NULL);
    // --snip--
    osMessageQueueDelete(event_queue); // deletes our message queue for cleanup
    return 0;
}
```
The above code creates a new event queue that will hold `InputEvent`s (from the `input` service).

In its parameters, we define that it will have:
- A maximum of 8 messages in the queue
- A message size of an InputEvent
- Default attributes (specified by NULL)