GWEN
====

A fork of GWEN, a C++ GUI library.

The original library can be found here: https://github.com/garrynewman/GWEN

About
=====

This repository is a fork of GWEN which I use in my personal projects.  Since the original repository no longer appears active, I decided to upload this version.

This fork contains a subset of the original repository's widgets.  If I did not directly need the widget, I removed it.  In addition, the only supported rendering and input systems are both SDL2.

Building
========

For my personal projects, I use CMake.  So, I do not have any solution files to upload which would be of any value.  However, I included a sample CMakeLists file to act as a starting point.  You will need to modify it to operate in your CMake ecosystem.  In addition, you could use the sample CMakeLists file as a guide to integrate the files into your build environment.  Sorry. :(

Integrating
===========

Here's some pseudo code to get started:

```

// Somewhere in your code base while the application is starting up...

// Create the renderer.
gwen_renderer = new Gwen::Renderer::SDL2(...);
gwen_renderer->Initialize();

// Create the skin.
gwen_skin = new Gwen::Skin::TexturedBase(gwen_renderer);
gwen_skin->Initialize(...);

// Create the canvas.
gwen_canvas = new Gwen::Controls::Canvas(gwen_skin);

// Create the input system.
gwen_input = new Gwen::Input::SDL2();
gwen_input->Initialize(gwen_canvas);

...

YourGameLoop()
{
    SDL_Event the_event;
    while (SDL_PollEvent(&the_event))
    {
        // Process events.
        gwen_input->ProcessEvent(the_event);

        ...

    }

    ...

    // Draw the canvas.
    gwen_canvas->RenderCanvas();
}

// Make sure to clean up the pointers.

...

```

In addition, to add a control:

```

button = new Gwen::Controls::Button(gwen_canvas);
button->SetText("Hello World");

```
