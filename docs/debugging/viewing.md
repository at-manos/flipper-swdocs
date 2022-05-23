---
sidebar_position: 10
---


# Viewing Logs in Real Time

## Reading Logs

<!-- rx -->
To recieve the logs provided on these levels, we need to set the device's log level in the settings.

To do this, we navigate to Applications->Settings->System

From here, you can set the log level of your flipper device.

<p align='center'>
<img src="/img/set_loglevel.gif"></img>
</p>


Now that you have your devices log level set up, we need to connect to the flipper over a serial connection.

There are many ways to see the serial line that your flipper is on, but the easiest is probably to just open up qFlipper.


![The top right of qFlipper with a device connected](../img/../your-first-program/img/tty1.png)

On my device, it seems to be on `/dev/ttyACM0`.

On Windows, it will typically be `COM`\*
On \*nix, it will typically be `/dev/tty`\*

## Interfacing with the CLI

### Windows

For Windows systems, I recommend [PuTTY](https://www.putty.org) to interface with your serial connection.

To connect to your serial line, select "Serial" under connection type, and type in the location.

<p align='center'>
<img src="/img/windows_putty.gif"></img>
</p>


Now, just enter `log` and there you go!

### *nix

There are many tools, but I would recommend [PuTTY](https://www.putty.org), or `screen`, a popular utility for linux.

<p align='center'>
<img src="/img/log.gif"></img>
</p>

Once inside the serial connection, type `log`, and now you can see your logs! 