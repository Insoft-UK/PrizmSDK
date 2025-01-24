# Getting started on macOS

This document will walk you through the process of setting up the <a href="https://github.com/Jonimoose/libfxcg">PrizmSDK</a> and building your first add-in on macOS.

## Download and unpack the PrizmSDK

Download an PrizmSDK package from the [releases page](https://github.com//Insoft-UK/libfxcg/releases/) and unpack to your Applications/CASIO folder.

![Extracted SDK package](img/sdk-dir.png)

## Look at the Example project

Navigate to `Projects`, then `Example`. This directory contains the example project to get you started with and looks like this:

![Example project directory layout](img/project-dir.png)

The `Icon~sel.bmp` and `Icon~uns.bmp` images are built into the compiled add-in and are the icons shown in the calculator's menus for the add-in when it is selected with the cursor and unselected, respectively.

`Makefile` is a plain-text file that includes instructions that tell the system how to compile the add-in. You can edit this with any text editor of your choice, but in most cases don't need to (and probably shouldn't unless you know what you're doing). If you're just getting started, it's safe to ignore this file. Similarly, `make` allows you to run a single command and compile the add-in and you shouldn't need to touch it.

![Example project directory layout](img/example-dir.png)

## Compile the Example project

To compile the Example project, simply run `make.sh` in the project directory
using the Terminal.

![Example project directory layout](img/open-terminal.png)

The `Example.g3a` file is ready to send to your calculator for running now.

![Example project directory layout](img/result.png)

## Making changes and rebuilding

Every time you run `make` as above, the system will rebuild the g3a file if there have been any changes to the sources. It's possible that won't always work as you expect, so you can also run `.\make clean` to erase the output files from the compilation process and ensure you're building a totally fresh version.

Using the provided **make** script in the Example folder will automatically clean up after building the 3ga file, streamlining the development process.

## Making your own project

Now that you know how to build an add-in, it's time to write your own program. Make a copy of the `Example` project and call it something else (probably a name related to what your project is), then you can write your own code however you like.
