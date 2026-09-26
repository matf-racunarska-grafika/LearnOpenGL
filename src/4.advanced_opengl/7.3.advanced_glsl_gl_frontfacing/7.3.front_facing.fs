#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    if (gl_FrontFacing)
        FragColor = texture(texture2, TexCoords);
    else
        FragColor = texture(texture1, TexCoords);
}