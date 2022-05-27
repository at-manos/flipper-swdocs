---
sidebar_position: 2
---

# Signature and structures

Now that we have `box_mover.c` in our `box_mover` folder, we can finally start programming.






## Model Struct
To make our lives easier, let's define all the information we need to encode for rendering our app:
- A point to render our box at, consisting of:
  - an `x` coordinate
  - and a `y` coordinate

Pretty simple! We'll do that by declaring a `BoxMoverModel` struct that holds that information.

```c title="box_mover/box_mover.c"
typedef struct {
    int x;
    int y;
} BoxMoverModel;
```

## Application Struct

Now that we're able to encode the information we need, let's create a struct that will hold all of the necessary variables and structures for our entire application.

This might seem a little odd at this point, but the benefits will show soon. This type of program structure is idiomatic with the rest of Flipper Zero's applications and will allow you to more easily transfer into other [GUI Paradigms](/docs/category/gui-paradigms) later down the line.

```c
typedef struct {
    BoxMoverModel* model;
} BoxMover;
```
For now, it'll just hold a pointer to our model. 

## Allocating and freeing functions

Now, let's write two functions that will allocate and free an instance of our `BoxMover` struct. Let's call them `box_mover_alloc` and `box_mover_free`

### Allocation 
```c
BoxMover* box_mover_alloc(){
    BoxMover* instance = malloc(sizeof(BoxMover));
    instance->model = malloc(sizeof(BoxMoverModel));
    instance->model->x = 10;
    instance->model->y = 10;
    
    return instance;
}
```
Our `box_mover_alloc` will allocate space for a BoxMover instance and subsequent model instance, and then initialize the model with some data. We return the instance at the end for our caller to use later.


### Freeing

```c
void box_mover_free(BoxMover* instance){
    free(instance->model);
    free(instance);
}
```
Since all we've done in our `box_mover_alloc` is allocate memory for our structs, we just need to use `free` to release that memory back.


## Main Signature

The function that will run our plugin's code will follow a simple signature, complying with the other applications:
```c
#include <furi.h>

// --snip--

int32_t box_mover_app(void* p){
    BoxMover* box_mover = box_mover_alloc();

    box_mover_free(box_mover);
    return 0;
}
```
This is how all applications are declared within Flipper Zero firmware, and it is common practice to append the name with `_app`.
:::info
To avoid unused errors, call `UNUSED(p)`.
:::




:::info Unsure of your code?
Check out the [code so far](https://github.com/at-manos/flipper-swdocs/tree/main/docs/your-first-program/code-so-far/sig-structs) for this section!
:::