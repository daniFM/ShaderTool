# ShaderTool

An OpenGL based tool to write and compile (post-processing) shaders.

## Features

- Preview your post-processing shader.
- Edit it with your favorite text editor.
- Save your shaders and open them.
- Apply your shader to any texture.

## About Shader Tool

Shader tool is programmed in C++. The code is divided in Data Model, Back-End and Front-End. The UI was made using nanogui and it is composed from a configurable layout in a xml.

The path to the data directory can be set by providing it as a cmd parameter.

The shader code is read and written using multi platform softare. I also made an small dynamic libraryto help with the path management.
