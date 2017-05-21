in vec4 frag_Col;
in vec2 frag_UV;

out vec4 final_Col;

//uniform sampler2D textureSampler;

void main() {
    final_Col = /*texture(textureSampler, frag_UV) * */frag_Col;
}