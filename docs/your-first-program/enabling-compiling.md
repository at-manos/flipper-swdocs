---
sidebar_position: 9
---

# Enabling and Compiling


## applications.c

We first need to add a reference to the main function we defined in `box_mover.c`, so that it shows up in our applications menu.

Let's add it right under the snake plugin.
```c title="/applications/applications.c"
    // Plugins
    extern int32_t music_player_app(void* p);
    extern int32_t snake_game_app(void* p);
    extern int32_t box_mover_app(void* p);
```

Great! Just one more place in this file, filling out the metadata for our application.


```c title="/applications/applications.c"
    #ifdef APP_SNAKE_GAME
        {.app = snake_game_app,
        .name = "Snake Game",
        .stack_size = 1024,
        .icon = &A_Plugins_14,
        .flags = FlipperApplicationFlagDefault},
    #endif

    #ifdef APP_BOX_MOVER
        {.app = box_mover_app, 
        .name = "Box Mover", 
        .stack_size = 1024, 
        .icon = &A_Plugins_14,
        .flags = FlipperApplicationFlagDefault},
    #endif
```


## applications.mk

To let the compiler know to compile our plugin, we need to add *two* entries to `applications.mk`.

Once, at the top of the file:
```txt title="/applications/applications.mk"
# Plugins
APP_MUSIC_PLAYER = 1
APP_SNAKE_GAME = 1
APP_BOX_MOVER = 1
```

and once more, below `APP_SNAKE_GAME`
```txt title="/applications/applications.mk"
APP_BOX_MOVER ?= 0
ifeq ($(APP_BOX_MOVER), 1)
CFLAGS		+= -DAPP_BOX_MOVER
SRV_GUI		= 1
endif
```

# Compiling

To compile your code, follow [these instructions in the setup](/docs/environment-setup/compiling)