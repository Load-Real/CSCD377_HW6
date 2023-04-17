#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

//Matrices
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

//Light Attributes
uniform vec4 LightPosition;
uniform vec3 LightColor;
uniform vec3 Ambient;
uniform vec3 MaterialColor;
uniform float Shininess;

out vec4 color;

void main(void)
{
    mat4 normalMatrix = transpose(inverse(view_matrix*model_matrix));
	vec4 eyeSpacePosition = view_matrix * model_matrix * position;
    vec3 eyeSpaceNormal = mat3(normalMatrix) * normal;

	//Normalized Vectors
    vec3 N = normalize(eyeSpaceNormal); //Normal
    vec3 L = normalize(LightPosition.xyz - eyeSpacePosition.xyz); //Light Direction
    vec3 V = normalize(vec3(0,0,0) - eyeSpacePosition.xyz); //Viewers Direction
    vec3 H = normalize(L+V); //Half Vector

    //Diffuse Reflection
    vec3 diffuse =  LightColor * (max(dot(L,N), 0.0));

    //Specular Reflection
    vec3 specular = LightColor * (pow(max(dot(N, H), 0.0), Shininess));

    //Final Light Calculation
    vec4 scatteredLight = vec4((Ambient + diffuse) * MaterialColor + specular, 1.0);
    
    //Final Color Calculation
    color = min(scatteredLight, vec4(1.0));

    //Position
	gl_Position = projection_matrix * view_matrix * model_matrix * position;
}

