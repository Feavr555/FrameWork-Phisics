#version 330 core

in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 color_in;

out vec3 color;

void main()
{
    vec3 n = normalize(Normal_cameraspace);
    vec3 l = normalize(LightDirection_cameraspace);

    float diff = max(dot(n, l), 0.0);

    // Ambiental mínima para que nunca sea negro
    float ambient = 0.15;

    float lighting = ambient + diff * 0.85;

    color = color_in * lighting;
}
