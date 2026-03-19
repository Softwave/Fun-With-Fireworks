#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform float threshold;
uniform float strength;

out vec4 finalColor;

void main()
{
    vec4 src = texture(texture0, fragTexCoord);
    float luma = dot(src.rgb, vec3(0.2126, 0.7152, 0.0722));
    float range = max(1.0 - threshold, 0.0001);
    float weight = clamp((luma - threshold) / range, 0.0, 1.0);

    vec3 bloom = src.rgb * weight * strength;
    finalColor = vec4(bloom, weight * src.a);
}
