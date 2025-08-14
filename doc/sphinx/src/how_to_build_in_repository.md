# Build in the Repository

This section show how to build this project in the Git repository.

Here shows two ways to build this project:

- [Build in DevContainer of Visual Studio Code](#build-in-devcontainer-of-visual-studio-code)
- [Build using Visual Studio in Windows](#build-using-visual-studio-in-windows)

## Build in DevContainer of Visual Studio Code

This section shows how to build this project
in DevContainer of Visual Studio Code.

### Prerequisites

- Install [Visual Studio Code](https://code.visualstudio.com/).
- Install [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) in Visual Studio Code.
- Install [Docker](https://www.docker.com/).

### Steps

1. Update Git submodules.

   Execute the following command in the directory of this project.

   ```shell
   git submodule update --init --recursive
   ```

2. Open the directory of this project with DevContainer.

   See
   [Developing inside a Container](https://code.visualstudio.com/docs/devcontainers/containers)
   for how to open a project with DevContainer.

   When you open this project with DevContainer for the first time,
   required configurations are automatically done.

3. Build this project.

   You can use
   [CMake Tools extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
   to build this project.

   When you build this project for the first time,
   dependencies are automatically downloaded and built.

   Also you can run tests with CMake Tools extension.

## Build using Visual Studio in Windows

This section shows how to build this project
using Visual Studio in Windows.

This project has configurations to build with Visual Studio in CMakePresets.json file.
For details, see
[CMake projects in Visual Studio](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170).

### Prerequisites

- Install [Visual Studio](https://visualstudio.microsoft.com/)

### Steps

1. Update Git submodules.

   Execute the following command in the directory of this project.

   ```shell
   git submodule update --init --recursive
   ```

2. Install Python dependencies.

   Execute the following command in the directory of this project.

   ```shell
   poetry sync
   ```

3. Open the directory of this project with Visual Studio.

   Visual Studio will automatically detect configurations written in CMakePresets.json file
   and run cmake to configure this project.

   When you open this project with Visual Studio for the first time,
   dependencies are automatically downloaded and built.

4. Build this project.

   You can build this project with Visual Studio, for example, by pressing Ctrl+Shift+B.

   Also you can run tests with Visual Studio.
