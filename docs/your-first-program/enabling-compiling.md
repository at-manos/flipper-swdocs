---
sidebar_position: 9
---

# Enabling and Compiling

Luckily this process has been streamlined, and we only need add a single line to reference our plugin ID in

and add the file `application.fam` for our plugin metadata in our application folder.

## Application Metadata

First, let's create an individual metadata file for our plugin:

```
.
└── flipperzero-firmware/
    └── applications/
        └── box-mover/
            └── application.fam
```

Inside, we're going to add some metadata about our application. 

```c title="/applications/box-mover/application.fam"
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

This file provides metadata about our application. The `appid` will be used to reference our plugin, and `entry_point` indicates our main function for execution when the plugin initiates.

## Linking to the applications list

To make our plugin accessible, we need to add an entry into the `/applications/meta/application.fam` file, with our plugin ID we created in the individual metadata.

```
.
└── flipperzero-firmware/
    └── applications/
        └── meta/
            └── application.fam
```

Let's add it to the "basic_plugins" list of applications.

```c title=/applications/meta/application.fam
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