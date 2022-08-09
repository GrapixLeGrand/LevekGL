# LevekGL

For now, this project is a OpenGL wrapper with the following features:

- openGL buffers binding
- glsl shader compilation with comprehensive error report from glslang
- model loading with Assimp
- Easy to link in your project

On Linux:

```
sudo apt-get update
sudo apt-get install libassimp-dev
```

Note that when using CMake, you might need to add the AssimpConfigure.cmake found in the official repo [here](https://github.com/assimp/assimp/blob/master/cmake-modules/Findassimp.cmake) as the installation does not add it by default.