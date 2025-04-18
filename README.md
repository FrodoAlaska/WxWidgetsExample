## Intro 

An example project using the wxWidgets library and OpenGL. 

## Dependencies 

- [wxWidgets](https://www.wxwidgets.org/)

## Build Instructions 

Before attempting to build this project, you'll first have to clone the project using the command below:

```bash
git clone --recursive https://github.com/FrodoAlaska/WxWidgetsExample.git
cd WxWidgetsExample
```

Notice the `--recursive` flags being passed to the `git clone` command. That is because this project uses `submodules` to manage its dependencies. The `--recursive` _has_ to be passed in order to have a successful build process.

After cloning the project, we can finally start the build process. As you can see, this project uses `cmake` as its build system. We first make a build directory specifically for the debug build configuration and "cd" into it. 
Afterwards, using the `cmake ..` command, CMake will generate a bunch of files for building

```bash
mkdir build-debug && cd build-debug
cmake .. 
```

Once CMake is done, we can actually start building. On Windows, we can use the `cmake --build .` command, passing in the `--config Debug` flag to build a debug configuration of the project. Of course, `Debug` can be substituted with `Release` if need be. On Linux, the same command can be used, or we can just use `make`.


```bash
# Windows 
cmake --build . Debug --parallel 8

# Linux 
make -j 8
```

You might have noticed the `--parallel` or `-j` flags. These flags tell the compiler to use a certain number of threads (8, in this case) to handle the build process. These flags can be omitted completely. However, since this project will build the `wxWidgets` library from source, it is recomended to have this flag.
