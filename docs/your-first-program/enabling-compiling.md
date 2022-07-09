---
sidebar_position: 9
---

# Enabling and Compiling

Luckily this process has been streamlined, and we only need add a single line to reference our plugin ID in

```
.
└── flipperzero-firmware/
    └── applications/
        └── meta/
            └── application.fam
```

and add the file `application.fam` for our plugin metadata in our application folder.

## Application Metadata

First we construct the metadata for our plugin

```title="/applications/box-mover/application.c"
   App(
    appid="box_mover_app",
    name="Box Mover",
    apptype=FlipperAppType.PLUGIN,
    entry_point="box_mover_app",
    cdefines=["APP_BOX_MOVER"],
    requires=["gui"],
    stack_size=1 * 1024,
    icon="A_Plugins_14",
    order=30,
)
```

The `appid` will be used to reference our plugin, and `entry_point` indicates our main function for execution when the plugin initiates.

Let's finally add reference to our plugin below snake

```title="/applications/meta/application.c
...

App(
    appid="basic_plugins",
    name="Basic applications for plug-in menu",
    apptype=FlipperAppType.METAPACKAGE,
    provides=[
        "music_player",
        "snake_game",
        "box_mover_app",
        "bt_hid",
    ],
)
```

and with that, we are ready to compile and flash!

# Compiling

To compile your code, follow [these instructions in the previous section](/docs/environment-setup/compiling)