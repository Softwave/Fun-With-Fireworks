#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec2 direction;

out vec4 finalColor;

void main()
{
    vec2 texel = 1.0 / vec2(textureSize(texture0, 0));
    vec2 offset = texel * direction;

    vec3 result = texture(texture0, fragTexCoord).rgb * 0.227027;
    result += texture(texture0, fragTexCoord + offset * 1.384615).rgb * 0.316216;
    result += texture(texture0, fragTexCoord - offset * 1.384615).rgb * 0.316216;
    result += texture(texture0, fragTexCoord + offset * 3.230769).rgb * 0.070270;
    result += texture(texture0, fragTexCoord - offset * 3.230769).rgb * 0.070270;

    finalColor = vec4(result, 1.0);
}
