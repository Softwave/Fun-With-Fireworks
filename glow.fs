#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float glowIntensity;
uniform float glowSize;

out vec4 finalColor;

void main()
{
    vec2 center = vec2(0.5, 0.5);
    vec2 uv = fragTexCoord - center;
    float distance = length(uv);
    
    // Circle glow fx 
    float glow = 1.0 - smoothstep(0.0, glowSize, distance);
    glow = pow(glow, 2.0);
    
    // base particlce 
    float core = 1.0 - smoothstep(0.0, 0.3, distance);
    core = pow(core, 4.0);
    
    // Combine core and glow
    float alpha = core + glow * glowIntensity;
    
    // Apply colour and brightness 
    vec3 color = fragColor.rgb * (1.0 + glowIntensity * 0.5);
    
    finalColor = vec4(color, alpha * fragColor.a);
}