# Licenca
Ovaj repozitorijum je fork originalnog [https://learnopengl.com](https://github.com/JoeyDeVries/LearnOpenGL) autora [Joey De Vries](https://joeydevries.com/#home)
i kao takav spada pod [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) licencu.
Ako nije drugačije naglašeno svi primeri su originalni. Na početku svakog fajla koji nije deo originalnog repozitorijuma je naglašeno 
da je dodat.

# learnopengl.com code repository
Contains code samples for all chapters of Learn OpenGL and [https://learnopengl.com](https://learnopengl.com). 

## Windows building
All relevant libraries are found in /libs and all DLLs found in /dlls (pre-)compiled for Windows. 
The CMake script knows where to find the libraries so just run CMake script and generate project of choice.

Keep in mind the supplied libraries were generated with a specific compiler version which may or may not work on your system (generating a large batch of link errors). In that case it's advised to build the libraries yourself from the source.

## Linux building
First make sure you have CMake, Git, and GCC by typing as root (sudo) `apt-get install g++ cmake git` and then get the required packages:
Using root (sudo) and type `apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev  libxi-dev` .

### Building from Terminal

To build the project, use the following commands:

```bash
cmake -S . -B build
cmake --build build --parallel
```

After building, the executables are located in the `bin/` directory, organized by chapter. For example, to run the "Hello Window" example:

```bash
cd bin/1.getting_started/
./1.getting_started__1.1.hello_window
```

Always run the executable from the directory where it is located.

### Troubleshooting Resources

If you encounter issues with missing resources (shaders, textures), ensure that the `LOGL_ROOT_PATH` environment variable is set correctly, although the default configuration should handle this automatically using the project root.

    `export LOGL_ROOT_PATH=/path/to/LearnOpenGL`

## Mac OS X building
Building on Mac OS X is fairly simple:
```
brew install cmake assimp glm glfw freetype
cmake -S . -B build
cmake --build build -j$(sysctl -n hw.logicalcpu)
```
## Create Xcode project on Mac platform
Thanks [@caochao](https://github.com/caochao):
After cloning the repo, go to the root path of the repo, and run the command below:
```
mkdir xcode
cd xcode
cmake -G Xcode ..
```

## Glitter
Polytonic created a project called [Glitter](https://github.com/Polytonic/Glitter) that is a dead-simple boilerplate for OpenGL. 
Everything you need to run a single LearnOpenGL Project (including all libraries) and just that; nothing more. 
Perfect if you want to follow along with the chapters, without the hassle of having to manually compile and link all third party libraries!

## Ports
Check out [@srcres258](https://github.com/srcres258)'s port in Rust [here](https://github.com/srcres258/learnopengl-rust/).
