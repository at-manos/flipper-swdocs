---
sidebar_position: 2
---

# Signature and structures

Now that we have `box_mover.c` in our `box_mover` folder, we can finally start programming.




### State Structure

To make our lives easier, let's define all the information we need to encode for our project:
- A point to render our box at, consisting of:
  - an `x` coordinate
  - and a `y` coordinate

Pretty simple! We'll do that by declaring a `GameState` struct that holds that information.

```c
typedef struct {
    int x;
    int y;
} GameState;
```

### Main Signature

The function that will run our plugin's code will follow a simple signature, complying with the other applications:
```c
#include <furi.h>
// --snip--
int32_t box_mover_app(void* p){

    return 0;
}
```
This is how all applications are declared within Flipper Zero firmware, and it is common practice to append the name with `_app`.
:::info
To avoid unused errors, just use `UNUSED(p)`.
:::

### Initializing our state
Now that we have our struct defined as a type, let's use it and initalize it with some data.
```c
#include <furi.h>
#include <stdlib.h>
// -snip-
void init_state(GameState* game_state){
    game_state->x = 10;
    game_state->y = 10;
}

int32_t box_mover_app(void* p){
    UNUSED(p);

    GameState* game_state = malloc(sizeof(GameState));
    init_state(game_state);

    return 0;
}
```



