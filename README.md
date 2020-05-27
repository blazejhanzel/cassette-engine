# Cassette Engine

## Description

Cassette Engine is a project made with idea to get making games in C++ easier. This is get by programming using only two type of scripts, **Tasks** and **Logics**. Another advantage is that Cassette Engine is released with static linked libraries like SFML and TGUI and with source code of some other useful libraries like Boost (using Boost::Any out-of-box, but feel free to use other functionalities), ColorSpace (for converting rgb, hsl, etc. values), inipp (for creating config files) and nlohmann's JSON (for more complicated config files). If you are a contributor, feel free to add other usefull libraries which license is free-to-use, even comercial.

 ## Installation

 At the moment there are dynamically-linked libraries builded only or Windows x64 and Visual Studio 2019 IDE. Feel free to build other versions and commit them here. If you don't use Windows x64 or Visual Studio you must download all sources and build code yourself.

 ### Installation for Visual Studio 2019

 1. Download content of this repo or chosen version from *Relases* tab.
 2. Copy include\msvc_x64 content to your projects include folder and include it in your project.
 3. Copy content of bin\msvc_x64 to directory where your binaries are executed.
 4. Copy code from below and run it, app will start if installation complete succesfully.

```
#include <cas/Core.h>

using namespace cas;

int main(int argc, char** argv) {
	// At the beggining get hock to core object
	pCore core = Core::get();

	// Process arguments from command line
	core->processArgs(argc, argv);

	// This is place for define loading instructions using cas::Task or by simple writing code

	// At the end run engine
	return core->run();
}
```

## How to use this engine?

### Managers

Cassette Engine is build from Core module, which controls all managers. Menagers built-in to engine are:

- **Audio Manager** - for controlling music and audio instances, because SFML and OpenAL have 255 instances limit and this managers controls this instances (delete if too much). It provide functionality to play soundtracks too.
- **Asset Manager** - for controlling all resources, keep them buffered and create gameobject prefabs.
- **Display Manager** - controls window and displaying hierarchy.
- **Engine Settings (Manager)** - save and load engine settings or load default in some reasons.
- **Event Manager** - for controlling events from system (keyboard, window, etc.).
- **Scene Manager** - controlls all scenes created by programmer. Scene is what is displayed exactly. Scenes are built from assets. Assets should be copied from Asset Manager.
- **State Manager** - controls state signals of engine. 

### Logger

There is Logger class too that can be used for logging some data into file and standard cout using one function. Use ```*(cas::Core::get()->getLogger()) << "content of message";``` (```std::endl``` is not needed).

### Tasks

You can write tasks, by inherts from cas::Task class. Think about class name, eg. StartupTask.

Your StartupTask.h file should look like this:

```
#pragma once

#include <cas/Task.h>

class StartupTask : public cas::Task {
	void task();
};
```

And your StartupTask.cpp should look like this:

```
#include "StartupTask.h"

#include <cas/Core.h>

using namespace cas;
using namespace sf;
using namespace std;

void StartupTask::task() {
	// Do what you want
    // Load resources using Asset Manager
    // Connect with server using Network Manager

	done(); // this is what tell engine that this task is done
}
```

**IMPORTANT!** You must remember to write ```done();``` at the end of ```task()``` method or you will stay in loading screen forever.

**PARALLEL NOTE:** Tasks are running simultaneously when in loading screen. Maximum number of tasks is computers cores amount. If you will create more tasks, engine will put them in to queue and runs next one when one of them ends job (using ```done();```). That means that you can have e.g. one task for loading resources for player and one for loading resources to enemies. This will speed up loading time, but remeber to not using resources in task A that are loaded in task B, because you don't know which thread will ends earlier.

### Logics

You can write logic scripts to control asset behaviours. Create class e.g. "Player". Header file should look like this:

```
#pragma once

class Player : public cas::Component::Logic {
public:
	void init(cas::pAsset asset, cas::pGui gui);
	void eventHandler(cas::pAsset asset, cas::pEvent event, cas::pGui gui);
	void update(cas::pAsset asset, cas::pGui gui);
};
```

You can use custom methods and variables too.

```void init``` is loaded once, after creating asset instance

```void eventHandler``` is for checking events, e.g. window resizables

```void update``` runs once per frame, use it to write scripts

Source file should defines ```init```, ```eventHandler``` and ```update``` methods.

### Documentation

Documentation for engine is written in Doxygen style **but** there is no HTML export. If you want to have HTML version of documentation, download Doxygen generator and generate documentation on your own.

## License

Cassette Engine is under zlib/png license, such like SFML and TGUI.

Copyright (c) 2020 Błażej Hanzel

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Some other libraries can use other licenses but versions included in this repo are using:

 - **Boost** - *Boost Software License*
 - **ColorSpace** - *MIT License*
 - **JSON** - *MIT License*
 - **inipp** - *MIT License*

 Some libraries, like SFML, use other, eg. OpenAL or OpenGL. You can read about it on libraries webpages.
