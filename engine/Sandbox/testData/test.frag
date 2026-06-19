#version 460 core
#extension GL_ARB_bindless_texture : require

in vec2 v_TexCoord;
flat in uvec2 v_Texture;

out vec4 FragColor;

void main() {
    if(v_Texture == uvec2(0, 0)){
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        return;
    }
    sampler2D texSampler = sampler2D(v_Texture);
    FragColor = texture(texSampler, v_TexCoord);
}
