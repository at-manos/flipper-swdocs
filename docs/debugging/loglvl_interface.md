---
sidebar_position: 1
---


# Log Levels and Interfacing

Very quickly, I want to touch on debugging. Crashes and unexpected behavior crops up a lot when working with something like this, and I don't think it would be prudent to not teach you how to debug your code.

## Log Levels
There are 6 different levels that a log can be set to
1. `None`
2. `Error`
3. `Warning`
4. `Info`
5. `Debug`
6. `Trace`


Each level supersedes the previous, meaning that at a `warning` log level, you will still recieve logs produced at the `error` level. 


## Printing logs

To log errors and information to our serial line, we are provided with 5 macros by furi's `log.h` header.

These are:

```c
FURI_LOG_E(tag, format, ...) 
FURI_LOG_W(tag, format, ...) 
FURI_LOG_I(tag, format, ...) 
FURI_LOG_D(tag, format, ...) 
FURI_LOG_T(tag, format, ...) 
```

The log level is denoted by the last character in the name. `FURI_LOG_E` being at `Error`, and so on.

Let's go through the parameters:
- `tag` specifies a tag to identify your program by. Make sure this is identifiable, and not something that could be confused.
- `format` specifies a cstring that will be the content of your message.
- The variadic parameters that follow behave the same as `printf` might, giving your format string the data it might display.

A call to this macro might look something like this:
```c
    FURI_LOG_I("BOX_MOVER", "x: %d, y:%d\n", x, y);
```