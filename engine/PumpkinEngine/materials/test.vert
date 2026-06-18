#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;

uniform float u_XOff;
uniform float u_Scale;

out vec3 inColor;

void main() {
    vec3 pos = a_Position * u_Scale;
    gl_Position = vec4(pos.x + u_XOff, pos.y, pos.z, 1.0);
    inColor = a_Color;
}
