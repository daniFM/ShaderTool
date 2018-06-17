# ShaderTool

An OpenGL based tool to write and compile (post-processing) shaders.

Shader Tool uses GLSL 3.30 core.

See the documentation [here](https://danifm.github.io/ShaderTool/) (generated with doxygen).

## Instructions

In the latest version of the repository you can run it with ShaderTool.exe or run.bat (Windows):
- By executing run.bat, you are using the assets folder in the root as the application directory.
- By executing ShaderTool.exe, youre using the data folder next to the executable.

![](https://raw.githubusercontent.com/daniFM/ShaderTool/master/docs/shadertool.JPG)

- **Preview button:** Updates the shader in the preview with the current shader.
- **Edit shader button:** Opens the shader to edit with the configured text editor.
- **Save button:** Saves the current shader with another name.By not using this, if you are editing the default "newShader" will be overwritten the next time you run the the program. You may provide the name without extension.
- **Open button:** Opens a new shader from the configured template. To do so, you must enter the name of the shader you want to open, without the extension.
- **Load texture button:** Loads and sets the texture from the provided name (with extension).

When the application is opened, a shader from the templates is read and copued to a "newShader.glsl", and a default texture is opened. You have to use the specified directory to work with Shader Tool.

### About the Visual Studio project

Shader Tool only works in the Debug - x86 configuration. All library routes, including dlls should be properly linked to the project. The solution contains the Shader Tool project as well as the Path Manager dynamic library. The path to the assets folder is passed as a parameter by default.

## Features

- Preview your post-processing shader.
- Edit it with your favorite text editor.
- Save your shaders and open them.
- Apply your shader to any texture.

## About Shader Tool

Shader tool is programmed in C++. The code is divided in Data Model, Back-End and Front-End. The UI was made using nanogui and it is composed from a configurable layout in a xml.

The path to the data directory can be set by providing it as a cmd parameter.

The shader code is read and written using multi platform softare. I also made an small dynamic libraryto help with the path management.
