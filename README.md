# Geant4_e---gamma--n
Geant4 simulation of the e- + gamma -> e- + gamma + n reaction. The simulation is based on the Geant4 example B5. 

## Pre-requisites

- Ubuntu 20.04 LTS
- Geant4 v11+ build with the following flags:
    ```shell
    $ cmake -DGEANT4_INSTALL_DATA=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo \ 
           -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_QT=ON -DGEANT4_USE_RAYTRACER_X11=ON ..
    ```
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

Find the needed executable in the `build` directory and just run. For example:

```shell
  $ cd build/source/simulation/
  $ ./simulation --g4
```

### Geant4 variables
In order to run Geant4, you need to set paths to the table data for physical processes as environment variables:
```shell
export G4ENSDFSTATEDATA="/usr/local/share/Geant4/data/G4ENSDFSTATE2.3" && \
export G4LEDATA="/usr/local/share/Geant4/data/G4EMLOW8.2" && \
export G4LEVELGAMMADATA="/usr/local/share/Geant4/data/PhotonEvaporation5.7" && \
export G4NEUTRONHPDATA="/usr/local/share/Geant4/data/G4NDL4.7" && \
export G4PARTICLEXSDATA="/usr/local/share/Geant4/data/G4PARTICLEXS4.0" && \
export G4RADIOACTIVEDATA="/usr/local/share/Geant4/data/RadioactiveDecay5.6"
```
If you installed Geant4 to a different directory, you need to change the paths accordingly.
e packages are missing, or you would like to use newer versions, reconfigure the `init-farm.sh` file and switch to other LCG release.