# LearnOpenGL – MATF fork

Code samples for every chapter of [learnopengl.com](https://learnopengl.com), by [Joey de Vries](https://joeydevries.com/#home). This is the fork used for the *Computer Graphics* (Računarska grafika) course at MATF, University of Belgrade. It adds a few extra examples and fixes to the original [JoeyDeVries/LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL).

Each sample is its own small executable, built from a single CMake project. You can build everything at once or just the chapter you are working on.

## Table of contents

1. [Repository structure](#repository-structure)
2. [Examples](#examples)
3. [Quick start](#quick-start)
4. [Installing dependencies and building](#installing-dependencies-and-building)
   - [Linux](#linux)
   - [macOS](#macos)
   - [Windows](#windows)
5. [Running the examples](#running-the-examples)
6. [Building a single example](#building-a-single-example)
7. [Adding your own example](#adding-your-own-example)
8. [Troubleshooting](#troubleshooting)
9. [License](#license)

---

## Repository structure

```
LearnOpenGL/
├── CMakeLists.txt        # Single build script; one executable per example
├── cmake/modules/        # Find modules (FindGLM, FindGLFW3, FindASSIMP, ...)
├── configuration/        # Templates configured by CMake (root_directory.h.in, VS .user file)
├── includes/             # Header-only / bundled headers (glad, KHR, stb_image, learnopengl/*, ...)
├── lib/                  # Precompiled libraries for Windows (glfw3, assimp, freetype, irrKlang)
├── dlls/                 # Precompiled Windows DLLs that must sit next to the executables
├── resources/            # Textures, models, fonts, audio and other assets used by the examples
├── src/                  # Source code, grouped by chapter, then by example
│   ├── glad.c            # OpenGL function loader (built as the GLAD library)
│   ├── stb_image.cpp     # Image loader (built as the STB_IMAGE library)
│   └── <chapter>/<example>/
│       ├── *.cpp         # Example source
│       └── *.vs *.fs *.gs  # Vertex / fragment / geometry shaders
├── bin/                  # (generated) Built executables, one subfolder per chapter
├── build/                # (generated) CMake build tree, if you use `-B build`
├── .github/              # CI / repository configuration
├── LICENSE.md
└── README.md
```

### How the build is organised

- `CMakeLists.txt` declares a list of **chapters** and, for each chapter, a list of **examples**.
- For every example it creates an executable named `<chapter>__<example>`, for instance `1.getting_started__2.1.hello_triangle`.
- Shader files (`.vs`, `.fs`, `.gs`) from the example folder are copied (Windows/Linux) or symlinked (macOS) next to the executable, so the program can load them using relative paths.
- Executables end up in `bin/<chapter>/`.
- `configuration/root_directory.h.in` is turned into `root_directory.h`, which lets the code locate `resources/` through the project root path. This can be overridden with the `LOGL_ROOT_PATH` environment variable.
- Default build type is **Debug**. C++17 is required.

### Third-party libraries

| Library | Purpose | Where it comes from |
|---|---|---|
| [GLFW 3](https://www.glfw.org/) | Window and input handling | System package (Linux/macOS), `lib/` + `dlls/` (Windows) |
| [GLAD](https://glad.dav1d.de/) | OpenGL function loader | Bundled (`src/glad.c`, `includes/`) |
| [GLM](https://github.com/g-truc/glm) | Math library (vectors, matrices) | System package (Linux/macOS), `includes/` (Windows) |
| [Assimp](https://github.com/assimp/assimp) | 3D model loading | System package (Linux/macOS), `lib/` + `dlls/` (Windows) |
| [stb_image](https://github.com/nothings/stb) | Image/texture loading | Bundled (`src/stb_image.cpp`, `includes/`) |
| [FreeType](https://freetype.org/) | Font rendering (text rendering chapter) | System package (Linux/macOS), `lib/` (Windows) |
| [irrKlang](https://www.ambiera.com/irrklang/) | Audio (Windows only, 2D game chapter) | `lib/` + `dlls/` |

---

## Examples

Examples live in `src/<chapter>/<example>/` and mirror the structure of the website.

| Chapter | Topics covered | Example executables (a selection) |
|---|---|---|
| `1.getting_started` | Window creation, triangles, shaders, textures, transformations, coordinate systems, camera | `1.1.hello_window`, `2.1.hello_triangle`, `3.3.shaders_class`, `4.2.textures_combined`, `6.3.coordinate_systems_multiple`, `7.4.camera_class` |
| `2.lighting` | Colors, Phong lighting, materials, lighting maps, light casters, multiple lights | `2.1.basic_lighting_diffuse`, `3.1.materials`, `4.2.lighting_maps_specular_map`, `5.3.light_casters_spot`, `6.multiple_lights` |
| `3.model_loading` | Loading models with Assimp | `1.model_loading`, `2.model_lighting` |
| `4.advanced_opengl` | Depth/stencil testing, blending, face culling, framebuffers, cubemaps, advanced GLSL, UBOs, geometry shaders, instancing, MSAA | `1.1.depth_testing`, `2.stencil_testing`, `5.1.framebuffers`, `6.1.cubemaps_skybox`, `9.2.geometry_shader_exploding`, `10.3.asteroids_instanced`, `11.1.anti_aliasing_msaa` |
| `5.advanced_lighting` | Blinn-Phong, gamma correction, shadow mapping, point shadows, normal/parallax mapping, HDR, bloom, deferred shading, SSAO | `1.advanced_lighting`, `3.1.3.shadow_mapping`, `3.2.1.point_shadows`, `4.normal_mapping`, `7.bloom`, `8.1.deferred_shading`, `9.ssao` |
| `6.pbr` | Physically based rendering and image-based lighting | `1.1.lighting`, `1.2.lighting_textured`, `2.1.2.ibl_irradiance`, `2.2.2.ibl_specular_textured` |
| `7.in_practice` | Debugging, text rendering | `1.debugging`, `2.text_rendering` |

> The `3.2d_game` (Breakout) project is currently commented out in `CMakeLists.txt`. The guest-article samples under `src/8.guest/` are listed in the CMake file but are not part of the default build.

### Added in the MATF fork

These examples are additions for teaching purposes and are in `1.getting_started`:

| Example | What it demonstrates |
|---|---|
| `2.6.hello_window_events` | Handling window and input events |
| `2.7.hello_triangle_indexed_extra_attrib` | Indexed drawing with an extra vertex attribute |
| `2.8.hello_triangle_extra_attrib` | Passing an extra attribute (e.g. color) to the shader |
| `2.9.hello_triangle_glcall_error` | Detecting and reporting OpenGL errors (`glGetError`) |

Files that are not part of the original repository carry a note at the top saying they were added.

---

## Quick start

### 1. Fork the repository

Do not clone this repository directly. Fork it first, so you have your own copy where you can commit your notes and code changes during class.

1. Sign in to GitHub and open <https://github.com/matf-racunarska-grafika/LearnOpenGL>.
2. Click the **Fork** button (top right) and choose your own account as the owner.
3. GitHub creates `https://github.com/<your-username>/LearnOpenGL`.

### 2. Clone your fork

Replace `<your-username>` with your GitHub username:

```bash
git clone https://github.com/<your-username>/LearnOpenGL.git
cd LearnOpenGL
```

Optionally, add the course repository as `upstream` so you can pull in updates from the instructors:

```bash
git remote add upstream https://github.com/matf-racunarska-grafika/LearnOpenGL.git
git fetch upstream
```

To get new changes later (or use the **Sync fork** button on GitHub):

```bash
git pull upstream master
```

### 3. Keep your notes

Commit your notes and code changes to your fork as you go:

```bash
git add .
git commit -m "Notes from class: hello triangle"
git push origin master
```

Tip: put notes in a separate folder such as `notes/` (for example `notes/01-hello-window.md`) so they stay apart from the example sources and are less likely to conflict when you pull updates from `upstream`. 
Or, even better, create your own branch and keep changes sperate from the main branch

```bash
git checkout -b annotated
# Make notes in class...
git add .
git commit -m "Notes from class: hello triangle"
git push -u origin HEAD
```

### 4. Install dependencies, then build

Install the dependencies for your platform (see [Installing dependencies and building](#installing-dependencies-and-building)), then:

```bash
cmake -S . -B build
cmake --build build --parallel
```

### 5. Run an example (from its own directory!)

```bash
cd bin/1.getting_started
./1.getting_started__1.1.hello_window
```

---

## Installing dependencies and building

You need a C++17 compiler, CMake 3.15 or newer, Git, and the libraries listed above. An OpenGL 3.3+ capable GPU and driver is required to run the samples.

### Linux

#### Debian / Ubuntu / Linux Mint

```bash
sudo apt update
sudo apt install -y g++ cmake git pkg-config \
    libglm-dev libassimp-dev libglfw3-dev libfreetype-dev \
    libgl-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libxxf86vm-dev
```

(On older releases `libfreetype-dev` may be called `libfreetype6-dev`, and `libgl-dev` may be `libgl1-mesa-dev`.)

#### Fedora

```bash
sudo dnf install -y gcc-c++ cmake git pkgconf-pkg-config \
    glm-devel assimp-devel glfw-devel freetype-devel \
    mesa-libGL-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel libXxf86vm-devel
```

#### Arch / Manjaro

```bash
sudo pacman -S --needed base-devel cmake git glm assimp glfw freetype2 mesa \
    libx11 libxrandr libxinerama libxcursor libxi libxxf86vm
```

#### Build

```bash
cmake -S . -B build                    # Debug by default
cmake --build build --parallel
```

For an optimised build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

Wayland users: GLFW from the distribution works through XWayland, so the X11 development packages above are still needed by this project's CMake script.

### macOS

Requires Xcode Command Line Tools and [Homebrew](https://brew.sh/).

```bash
xcode-select --install          # skip if already installed
brew install cmake assimp glm glfw freetype
```

Build:

```bash
cmake -S . -B build
cmake --build build --parallel
```

Notes:

- macOS supports OpenGL only up to version 4.1 (deprecated by Apple). Examples that need newer features, such as compute shaders from the guest articles, will not run.
- Shaders are symlinked into `bin/<chapter>/` instead of copied, so edits to shader files take effect on the next run without rebuilding.
- If CMake cannot find a Homebrew library, pass the prefix explicitly: `cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix)"`.

### Windows

All required libraries are shipped with the repository: headers in `includes/`, import libraries in `lib/`, and DLLs in `dlls/`. You only need a compiler and CMake.

#### Option A: Visual Studio (recommended)

1. Install [Visual Studio](https://visualstudio.microsoft.com/) with the **Desktop development with C++** workload (this includes CMake), or install [CMake](https://cmake.org/download/) separately.
2. Install [Git for Windows](https://git-scm.com/download/win).
3. Open *x64 Native Tools Command Prompt for VS* or PowerShell and run:

```powershell
git clone https://github.com/matf-racunarska-grafika/LearnOpenGL.git
cd LearnOpenGL
cmake -S . -B build
cmake --build build --config Debug --parallel
```

Or generate the solution and open it in the IDE:

```powershell
cmake -S . -B build
start build\LearnOpenGL.sln
```

Every example is a separate project in the solution; set the one you want as the startup project. The working directory for each project is configured for you.

#### Option B: with winget

```powershell
winget install Git.Git Kitware.CMake Microsoft.VisualStudio.2022.BuildTools
```

Then, in the Visual Studio Build Tools installer, add the **Desktop development with C++** workload, and follow Option A.

#### Copy the DLLs

The executables need the DLLs from `dlls/` at runtime. Copy them next to the binaries (once per output folder):

```powershell
Copy-Item dlls\*.dll bin\1.getting_started\Debug\
```

Repeat for each chapter folder you want to run, or copy them into every `bin\<chapter>\Debug\` folder.

#### Precompiled library mismatch

The bundled libraries were built with a specific compiler version. If you get many linker errors, your compiler is probably incompatible. Build GLFW, Assimp and FreeType from source with your compiler and replace the files in `lib/` and `dlls/`.

#### Alternative: MSYS2 / MinGW

The bundled `lib/` files target MSVC. With MSYS2 (UCRT64 shell) you would instead use the system packages, which this CMake script does not currently look up on Windows, so MSVC is the supported route.

---

## Running the examples

After a successful build, executables are in `bin/<chapter>/`:

```
bin/
└── 1.getting_started/
    ├── 1.getting_started__1.1.hello_window
    ├── 1.getting_started__2.1.hello_triangle
    └── *.vs / *.fs / *.gs     # shaders copied by CMake
```

**Always run an executable from the directory it is located in.** The shaders are loaded by relative path.

```bash
# Linux / macOS
cd bin/2.lighting
./2.lighting__2.2.basic_lighting_specular
```

```powershell
# Windows (Visual Studio generator)
cd bin\2.lighting\Debug
.\2.lighting__2.2.basic_lighting_specular.exe
```

Textures and models are found through the project root path baked in at configure time. If you move the repository after configuring, re-run CMake or set:

```bash
export LOGL_ROOT_PATH=/path/to/LearnOpenGL      # Linux / macOS
$env:LOGL_ROOT_PATH = "C:\path\to\LearnOpenGL"  # Windows PowerShell
```

---

## Building a single example

Use the target name `<chapter>__<example>`:

```bash
cmake --build build --target 1.getting_started__2.1.hello_triangle
```

List all available targets:

```bash
cmake --build build --target help
```

---

## Adding your own example

1. Create a folder `src/<chapter>/<your_example>/` with your `.cpp` file and any `.vs` / `.fs` / `.gs` shaders.
2. Add `<your_example>` to the matching chapter list (e.g. `set(1.getting_started ... )`) in `CMakeLists.txt`.
3. Re-run CMake and build:

```bash
cmake -S . -B build
cmake --build build --target <chapter>__<your_example>
```

Include shared helpers with `#include <learnopengl/shader_m.h>`, `<learnopengl/camera.h>`, `<learnopengl/model.h>` and so on, and use `FileSystem::getPath("resources/...")` to reference assets.

---

## Troubleshooting

| Problem | Fix |
|---|---|
| `Could not find GLM / GLFW3 / ASSIMP` | A dev package is missing. Re-run the install command for your platform. On macOS try `-DCMAKE_PREFIX_PATH="$(brew --prefix)"`. |
| Linker errors about `X11`, `Xrandr`, `Xi`, `Xcursor`, `Xinerama`, `GL` (Linux) | Install the X11 and Mesa development packages from the Linux section. |
| Black window, or crash on `gladLoadGLLoader` | Your GPU/driver does not provide OpenGL 3.3 core. Update drivers; on VMs enable 3D acceleration. |
| Shaders or textures not found | Run the executable from its own folder, or set `LOGL_ROOT_PATH`. |
| `Failed to create GLFW window` on macOS | The sample must request a forward-compatible 3.3 core context (the examples already do this). Avoid running over SSH or without a display. |
| Many link errors on Windows | Bundled libs do not match your compiler version. Rebuild the libraries from source. |
| `.dll was not found` on Windows | Copy the DLLs from `dlls/` next to the executable. |
| Stale configuration after moving the repo | Delete `build/` and `bin/`, then re-run CMake. |

---

## Other resources

- Book and website: <https://learnopengl.com>
- Original repository: <https://github.com/JoeyDeVries/LearnOpenGL>
- [Glitter](https://github.com/Polytonic/Glitter): a minimal boilerplate that bundles all libraries, handy if you want to follow along with a single project.

---

## License

This repository is a fork of the original [LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL) by [Joey de Vries](https://joeydevries.com/#home) and is released under the [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) license. Unless stated otherwise, all examples are original. Files added in this fork are marked as such at the top of the file.
