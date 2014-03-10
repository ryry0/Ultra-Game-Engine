# Ultra Game 
Alpha version of the ULTRA game
*name subject to change*

## To compile on Windows:

1. Download the SDL 2.0.1 development libraries for MINGW/VISC++ at
[sdl.org](http://www.libsdl.org/download-2.0.php)

2. If using Code::Blocks:

	Copy the directories `{bin, include, lib}` in 

	`SDL..\..\i686-w64-mingw32` to 

	`ext\SDL\{bin, include, lib}`

3. Go to `Project -> Properties... -> Project's Build Options ... -> Search Directories -> Compiler`

	Add your path, e. g.: 

	`ext\SDL\include`

4. Then go to the `Linker` Search Directories tab and add

	`ext\SDL\lib`

5. Go to Linker settings tab and add:

	`-lmingw32 -lSDL2main -lSDL2 -lopengl32`

6. Copy `ext\SDL\bin\SDL2.dll` to the executable directory: `bin`

Tutorial can be referenced here:
[lazyfoo](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/codeblocks/index.php)

## To install SDL_image libraries:
1. Download the development libraries for MinGW from [sdl.org](www.libsdl.org/projects/SDL_image/)

2. Merge the i686 subfolders in this tree with the directory specified in the above
instructions.

3. Copy the `*.dll` files from:
	`ext\SDL\bin\*.dll`
	to the executable directory: `bin`

## To install further SDL Libraries, 

1. Download the development libraries.
2. Merge with Library tree.
3. Copy `*.dll`'s to local bin directory.

TODO:

1. Write window manager code for:

	-Windows

	-Linux

	-> Decided to use SDL, since it powers many popular indie games 
	(Amnesia, FTL, Don't Starve, and Portal)

	For windowing, threads, audio, network.

	Gives me a more portable way of cross platform implementation, 
	instead of having to write audio handling from scratch.


2. Make simple opengl implementation of sidescrolling schmup.

	-Physics

	-Mechanics

	-Texturing
