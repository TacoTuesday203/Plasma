in vec2 vert_Pos;
in vec4 vert_Col;
in vec2 vert_UV;

out vec4 frag_Col;
out vec2 frag_UV;

uniform mat4 camera;

void main() {

    gl_Position = camera * vec4(vert_Pos, 0.0, 1.0);
    
    frag_Col = vert_Col;
    frag_UV = vec2(vert_UV.x, 1.0 - vert_UV.y);
}