#version 330 core
out vec4 FragColor;

in vec2 TexCoords;


uniform sampler2DMS screenTexture;

void main()
{
    ivec2 viewportDim = ivec2(800, 600);
    ivec2 coords = ivec2(viewportDim * TexCoords);
    vec3 sample0 = texelFetch(screenTexture, coords, 0).rgb;
    vec3 sample1 = texelFetch(screenTexture, coords, 1).rgb;
    vec3 sample2 = texelFetch(screenTexture, coords, 2).rgb;
    vec3 sample3 = texelFetch(screenTexture, coords, 3).rgb;

    vec3 col = 0.25 * (sample0 + sample1 + sample2 + sample3);

    float grayscale = 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;
    FragColor = vec4(vec3(grayscale), 1.0);
} 