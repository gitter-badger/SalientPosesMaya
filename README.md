# SalientPosesMaya

Description coming soon


## IDE Setup

To help testing and development across multiple operating systems, I've used Chad Vernon's [cgcmake](https://github.com/chadmv/cgcmake) repository (almost) automatically set up my build environment.

To clone and setup the build environment, you can do the following:

```
git clone --recursive https://github.com/richard-roberts/SalientPosesMaya.git
cd SalientPoses/cgcmake

cmake -G <IDE> -DMAYA_VERSION=<YEAR> ../
```

Make sure to replace `<IDE>` and `<YEAR>` with the appropriate values. For example, on OSX one might use the command `cmake -G Xcode -DMAYA_VERSION=2016 ../`. After these steps, you can open the project in the IDE.


#### Issues 

I've found a few minor issues, these are listed below:

- Sometimes cmake cannot find the `common.cpp` file. You can temporarily remove this file from `src/CMakeLists.txt` , run the cmake command as above, and then add the `common.cpp` file back into your IDE project.

- My 2016 edition of Maya requires a deprecated development kit (I've stored a copy [here](https://github.com/richard-roberts/Maya-devkit)). Unfortunately, on `OSX`, this development kit depends on the deprecated `libstdc++` library. 
    - When linking, add the flag `-stdlib=libstdc++`
    - In XCode, add the flag to `Build Settings - > Other Linker Flags`