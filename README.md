# Geant4_e---gamma--n
Geant4 simulation of the e- + gamma -> e- + gamma + n reaction. The simulation is based on the Geant4 example B5. 

## Pre-requisites

- Ubuntu 20.04 LTS
- Geant4 v11+ build with the following flags:
    ```shell
    $ cmake -DGEANT4_INSTALL_DATA=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo \ 
           -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_QT=ON -DGEANT4_USE_RAYTRACER_X11=ON ..
    ```
- Low Energy Nuclear Data (LEND) v1.3 - download it from [here](ftp://gdo-nuclear.ucllnl.org/) (ftp link) and copy into `/usr/local/share/Geant4/data/`.
- Cmake v3.24+
- git v2.7.4+
- Qt

## Pulling the repository
Pull the repository with the submodules:
```shell
$ git clone --recurse-submodules https://github.com/IvanBilinskyi/Geant4_e---gamma--n.git
```

## Build

1. Configure the CMake project using appropriate preset:
   ```shell
    # You can use the `default` preset, or configure another
    $ cmake -S . -B build --preset=default
   ```
   
2. Build:
   ```shell
   $ cmake --build --preset=default --target simulation -- -j4
   ```

## Run

1. Configure the Geant4 environment:
    ```shell
    $ bash /usr/local/share/Geant4/geant4make/geant4make.sh
    $ export G4LEDATA="/usr/local/share/Geant4/data/LEND_GND1.3_ENDF.BVII.1"
    ```
    If you installed Geant4 to a different directory, you need to change the paths accordingly.

2. Find the needed executable in the `build` directory and just run. For example:
    ```shell
    $ cd build/source/simulation/
    $ ./simulation --g4
    ```

