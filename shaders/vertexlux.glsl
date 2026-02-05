#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 color_in;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;
uniform vec3 color_out;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);

	Position_worldspace = (M * vec4(vertexPosition_modelspace, 1.0)).xyz;

	vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1.0)).xyz;

	// Vector hacia la cámara (0,0,0 en espacio cámara)
	EyeDirection_cameraspace = -vertexPosition_cameraspace;

	// Posición de la luz en espacio cámara
	vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1.0)).xyz;

	// Vector desde el vértice hacia la luz
	LightDirection_cameraspace = LightPosition_cameraspace - vertexPosition_cameraspace;

	Normal_cameraspace = normalize((V * M * vec4(vertexNormal_modelspace, 0.0)).xyz);

	UV = vertexUV;
	color_in = color_out;
}
