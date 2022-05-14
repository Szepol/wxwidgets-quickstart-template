
# **<p align="center">wxWidgets Quickstart Template </p>**

<p align="center">A template to quickstart wxWidgets projects<p>

 ## Features

 - Cpplint for code linting
 - Continuous integration using github actions
 - Google test unit testing
 - CPM for Dependencies management

## Requirements
 - CMake and A CMake generator of your choice
 - Git

## Usage

To generate a new repository using this template you can follow these [steps](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template#creating-a-repository-from-a-template)

### Fetch libraries with CMake.

#### Windows - MSVC

1. Open the repository with Microsoft Visual Studio.
2. Go make a coffee it might take around 15 minute. \
*Recommended:* Cancel the automatic generation, go to **Project -> CMake Settings for project** and add `-DCPM_SOURCE_CACHE=<path to an external download directory>` in **CMake** command arguments to prevent delete cache from removing the libraries source.
3. Once the CMake generation is finished, select the CMakeLists.txt in the root directory. \
*Recommended:* go to **Project -> CMake Settings for project** and add `-parallel=8` in **Build** command arguments to build the project faster, save the settings once it's done.
4. Click on **Select Startup Item** and select current document

#### Windows - CMake & Ninja

```bash
 mkdir build && cd build
 cmake .. -DCPM_SOURCE_CACHE=<path to an external download directory>
 cmake --build . --parallel=<number of jobs> --config=<Configuration type>
 ```

#### Linux

```bash
sudo apt-get install -y build-essential libgtk-3-dev libglew-dev
git clone <your generated repository>
cd <your generated repository>
mkdir build && cd build
cmake .. -DCMAKE_CXX_COMPILER=g++ -DCPM_SOURCE_CACHE=<path to an external download directory>
cmake --build . --parallel=<number of jobs> --config=<Configuration type>
```

### Build wxWidgets yourself.

 1. Download the executable or compressed files from [wxWidgets](https://github.com/wxWidgets/wxWidgets/releases/tag/v3.1.6)
 2. Rename the installation folder to `wxWidgets`
 3. Build wxWidgets and place the built libraries in the source folder \
 *e.g.* move `~\wxWidgets\build\lib\vc_x64_dll` to `~\wxWidgets\lib\vc_x64_dll`

 *Windows: Add the `<full-path>\wxWidgets\lib\vc_x64_dll` to your environment variable if want to build with shared libraries*

### Linux built-in libraries

```
sudo apt-get install -y libwxgtk3.0 libgtest-dev
```

## License
[MIT](https://github.com/Szepol/wxwidgets-quickstart-template/blob/main/LICENSE)