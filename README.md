# scramble-visualizer

A 2D virtual Rubik's Cube written in C++.

The main program can take any algorithm in [WCA notation](https://www.worldcubeassociation.org/regulations/#12a) and apply it to the virtual cube to show the resultant state.

## Screenshots
![3x3 Superflip](https://user-images.githubusercontent.com/46148388/83342098-113bc280-a2b9-11ea-99b0-44f217dc21c1.png)
![6x6 Scramble](https://user-images.githubusercontent.com/46148388/83342100-16007680-a2b9-11ea-99c9-ad13e1438f5e.png)
![9x9 Scramble](https://user-images.githubusercontent.com/46148388/83342103-1ac52a80-a2b9-11ea-9ff8-ed4bb672ef78.png)

## Compiling

You need:
* SFML 2.5+ development headers and library
* C++17 compliant compiler
* CMake build system

To compile, run CMake on the project directory with `CMAKE_BUILD_TYPE=Release`
and you'll get Makefile or equivalent for your platform, with which you can compile the project.

On Linux and macOS:
```fish
~ $ git clone https://github.com/HueFlux/scramble-visualizer.git
~ $ cd scramble-visualizer
~/scramble-visualizer $ mkdir build/ && cd build/
~/scramble-visualizer/build $ cmake -DCMAKE_BUILD_TYPE=Release ..
~/scramble-visualizer/build $ make
```

## Command-Line Version

<img src="https://user-images.githubusercontent.com/46148388/83342251-274a8280-a2bb-11ea-93a0-92cd53172400.png" alt="Command-Line 5x5" width="450"/> <img src="https://user-images.githubusercontent.com/46148388/83342252-2ca7cd00-a2bb-11ea-93a6-18f6b5d02d75.png" alt="Command-Line 5x5" width="450"/>

By default, the SFML version of the project will be built with the method above. If you would instead like to build the command-line version of this project which does not use SFML, you need to run CMake with `COMMAND_LINE=ON`.

On Linux and macOS:
```fish
~ $ git clone https://github.com/HueFlux/scramble-visualizer.git
~ $ cd scramble-visualizer
~/scramble-visualizer $ mkdir build/ && cd build/
~/scramble-visualizer/build $ cmake -DCMAKE_BUILD_TYPE=Release -DCOMMAND-LINE=ON ..
~/scramble-visualizer/build $ make
```

## Switching Between Versions

It is important to note that CMake cache variables persist during reruns of CMake, so in order to switch to the SFML version of the project after building the command-line version, you must either rerun CMake with `COMMAND_LINE=OFF` or remove `CMakeCache.txt` from the build directory and rerun CMake normally.

On Linux and macOS:
```fish
~/scramble-visualizer/build $ cmake -DCMAKE_BUILD_TYPE=Release -DCOMMAND-LINE=OFF ..
~/scramble-visualizer/build $ make
```
or
```fish
~/scramble-visualizer/build $ rm CMakeCache.txt
~/scramble-visualizer/build $ cmake -DCMAKE_BUILD_TYPE=Release ..
~/scramble-visualizer/build $ make
```

## Changing Cube Size

By default, the virtual Rubik's Cube is a 3x3x3. To change the size of the cube you must change the size value `N` in `include/cube.hpp` to the desired size
```cpp
class Cube {
    public:
        static const unsigned int N = 3; // Size (Creates a 3x3x3)
```
and then recompile the project with make or an equivalent.

On Linux and macOS:
```fish
~/scramble-visualizer/build $ make
```
The visualizer should work for any positively sized cube within the memory constraints of your particular system.

Yes, that does mean you can have a trivial 1x1x1 Rubik's Cube:

<img src="https://user-images.githubusercontent.com/46148388/83342689-3d0e7680-a2c0-11ea-86d6-1d720e8dff76.png" alt="Big Brain Cube" width="450"/>
