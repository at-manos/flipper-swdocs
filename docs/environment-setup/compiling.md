---
sidebar_position: 7
---

# Compiling

## Docker

Instead of installing the toolchain manually, we are provided with a docker configuration, so we can use that!

# Initializing the docker instance

1. Ensure that your machine has access to `docker` and `docker-compose`. On Windows, make sure Docker is running
2. Ensure you are in the root directory, with the *docker* folder.
3. Run the following command to set up the container in detached mode.
   ```bash
        docker-compose up -d
   ```
   <!-- *This will set up the container in detached mode.* -->

**You now have the docker container running in the background!**

## Compiling for the first time

Let's compile this firmware and get an idea of what that process looks like!

:::info
You will need Python installed for access to packages required by the assets build scripts
:::

1. In the root directory, install Python packages required by assets build scripts by running
   ```bash
   pip3 install -r scripts/requirements.txt 
   ```
2. Begin building by running the following command:
   ```bash
      docker-compose exec dev ./fbt
   ```

   In the end, your output should look something like this:
   
   ```
         BIN     build/f7-firmware-D/firmware.bin
   Building compilation database build/f7-firmware-D/compile_commands.json
         DFU     build/f7-firmware-D/firmware.dfu
   2022-07-09 09:05:21,711 [INFO] Firmware binaries can be found at:
         dist/f7-D
   ```


<!-- ## Brew

If you're on macOS, you might be already familiar with [Brew](https://brew.sh/). The maintainers at Flipper provide a brewfile in the repository, so we can take advantage of that and get the necessary utilities from the brewfile.

Let's first install the necessary utilities:
```sh
brew bundle --verbose
``` -->

   
### Your .dfu to flash is now located in `dist/f7-D/flipper-z-{target}-full-{suffix}.dfu`

:::info
For more information on the flipper build tool, see firmware documentation:
https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/fbt.md
:::
