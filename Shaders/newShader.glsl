#version 330

layout (location = 0) in vec3 vertex_coordinates;
layout (location = 1) in vec2 vertex_texture_uv;

out vec2 texture_uv;

void main()
{
   gl_Position = vec4(vertex_coordinates, 1.0);
   texture_uv  = vertex_texture_uv;
}

#version 330

uniform sampler2D sampler2d;

in  vec2 texture_uv;
out vec4 fragment_color;

void main()
{
    vec3 color = texture (sampler2d, texture_uv.st).rgb;
    float i = (color.r + color.g + color.b) * 0.3333333333;
    fragment_color = vec4(vec3(i, i, i) * vec3(1.0, 0.75, 0.5), 1.0);

    //fragment_color = vec4(1, 0, 0, 1);
}