#version 460 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;

layout(std140, binding = 1) uniform Material {
    vec2 u_Offset;
    float u_Scale;
};

out vec3 inColor;

void main() {
    vec2 pos = a_Position * u_Scale;
    gl_Position = vec4(pos.x + u_Offset.x, pos.y + u_Offset.y, 0.0, 1.0);
    inColor = a_Color;
}
