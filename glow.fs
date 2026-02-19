#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float glowIntensity;
uniform float glowSize;

out vec4 finalColor;

// Glow shader
void main()
{
    vec2 center = vec2(0.5, 0.5);
    vec2 uv = fragTexCoord - center;
    float distance = length(uv);
    float glow = 1.0 - smoothstep(0.0, glowSize, distance);
    glow = pow(glow, 2.0);
    float core = 1.0 - smoothstep(0.0, 0.3, distance);
    core = pow(core, 4.0);
    float alpha = core + glow * glowIntensity;
    vec3 color = fragColor.rgb * (1.0 + glowIntensity * 0.5);
    finalColor = vec4(color, alpha * fragColor.a);
}