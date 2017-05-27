#version 400 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 viewPos;


out vec3 o_normal;
out vec3 o_lightVector;
out vec3 o_viewVector;  //in view space


void main()
{
    vec4 positionWorld = model * vec4(position, 1.0);
    vec3 normalWorld = mat3(transpose(inverse(model))) * normal;

    o_lightVector = lightPos - positionWorld.xyz;
    o_viewVector = -vec3(view  * positionWorld);
    o_normal = normalWorld;

    gl_Position = projection * view * model * vec4(position, 1.0f);
}
