#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 2) out;

in vec3 vsColor[];
out vec3 fColor;


void main() {    
    vec4 position = gl_in[0].gl_Position;
    fColor = vsColor[0];
    gl_Position = position + vec4(-0.2, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(0.2, 0.0, 0.0, 0.0);
    EmitVertex();
    EndPrimitive();
}