#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormalCoord;


out vec2 TexCoord;
out vec3 normalVec, lightVec;

uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void){
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;

    normalVec = aNormalCoord*mat3(inverse(model));

    lightVec = lightPos - (model * vec4(0,0,0, 1.0)).xyz;
    lightVec = lightPos - (model * vec4(aPos, 1.0)).xyz;
} 