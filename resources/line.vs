#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 P;

void main()
{
    gl_Position = P * vec4(position, 1.0f);
}
