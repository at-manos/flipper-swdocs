---
sidebar_position: 9
---

# Enabling and Compiling

Luckily this process has been streamlined, and we only need add a single line to reference our plugin ID in

and add the file `application.fam` for our plugin metadata in our application user folder.

## Application Metadata

First, let's create an individual metadata file for our plugin:

```
.
└── flipperzero-firmware/
    └── applications_user/
        └── box-mover/
            └── application.fam
```

Inside, we're going to add some metadata about our application. 

```c title="/applications_user/box-mover/application.fam"
   App(
    appid="box_mover_app",
    name="Box Mover",
    apptype=FlipperAppType.EXTERNAL,
    entry_point="box_mover_app",
    requires=["gui"],
    stack_size=1 * 1024,
)
```

This file provides metadata about our application. The `appid` will be used to reference our plugin, and `entry_point` indicates our main function for execution when the plugin initiates.

## Adding an icon for the applications

To make our icon, we need to add 10x10px png in the same folder that the `/applications_user/box-mover/application.fam` file.

```
.
└── flipperzero-firmware/
    └── applications_user/
        └── box-mover/
            ├── application.fam
            └── icon.png
```

and we need to add the icon to the `application.fam`

```c title=/applications_user/box-mover/application.fam
...

   App(
    appid="box_mover_app",
    name="Box Mover",
    apptype=FlipperAppType.EXTERNAL,
    entry_point="box_mover_app",
    requires=["gui"],
    stack_size=1 * 1024,
    fap_icon="icon.png",
)
```

and with that, we are ready to compile and flash!

# Compiling

To compile your code, just use this command

```bash
./fbt fap_box_mover_app
```

The `./fbt fap_app_id` command allow to build any application by it's app_id.

Your `box_mover.fap` file could be found inside the `/flipperzero-firmware/build/f7-firmware-D/.extapps` folder.