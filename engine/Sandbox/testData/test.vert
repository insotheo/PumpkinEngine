#version 460 core
#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_UV;

layout(std140, binding = 1) uniform Material {
    vec2 u_Offset;
    float u_Scale;
    uvec2 u_Texture;
};

out vec2 v_TexCoord;
flat out uvec2 v_Texture;

void main() {
    vec2 pos = a_Position * u_Scale;
    gl_Position = vec4(pos.x + u_Offset.x, pos.y + u_Offset.y, 0.0, 1.0);
    
    v_TexCoord = a_UV;
    v_Texture = u_Texture;
}
