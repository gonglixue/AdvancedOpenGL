#version 400 core


in vec3 lightVector;
in vec3 viewVector;
in vec3 Normal;
out vec4 color;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	vec3 frag_normal = normalize(Normal);
	vec3 frag_lightVector = normalize(lightVector);
	vec3 frag_viewVector = normalize(viewVector);
	
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse;
    //float diff = max(dot(frag_normal, lightDir), 0.0);
	float diff = dot(frag_lightVector, frag_normal);
	diff = (diff+1.0)*0.5;
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5f;

    vec3 reflectDir = reflect(frag_lightVector, frag_normal);
    float spec = pow(max(dot(frag_viewVector, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
	//vec3 test = vec3(1.0f, 1.0f, 1.0f);
    color = vec4(result, 1.0f);
}
