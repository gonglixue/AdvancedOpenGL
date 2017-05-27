#version 400 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec3 Normal;
out vec3 lightVector;
out vec3 viewVector;

void main()
{
		vec4 posInWorld = model * vec4(position, 1.0f);
		vec3 normalInWorld = mat3(transpose(inverse(model))) * normal;
		
		// out
		lightVector = lightPos - posInWorld.xyz;
		viewVector = -vec3(view * posInWorld);
		
        gl_Position = projection * view * model * vec4(position, 1.0f);
        Normal = normalInWorld;
        
}
