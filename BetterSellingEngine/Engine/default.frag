#version 460 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 normalVec, lightVec;

uniform vec3 color;

uniform bool hasTexture;
uniform sampler2D textureData;

uniform bool usingLighting;

void main(void){

vec3 N = normalize(normalVec);
vec3 L = normalize(lightVec);

// calculates Kd (diffuse)
vec3 Kd = color;
if(hasTexture){
	vec4 texColor = texture(textureData, TexCoord);
	if (texColor.a < 0.1) discard;
	Kd = (texColor * vec4(color, 1.0f)).xyz;
}


if(usingLighting){
	//FragColor.xyz = vec3(0.5,0.5,0.5)*Kd + Kd*max(dot(L,N),0.0);
	FragColor.xyz = vec3(0.5,0.5,0.5)*(Kd + Kd*max(dot(L,N),0.0));
}
else{
	FragColor = vec4(Kd, 1.0f);
}


if(FragColor.x+FragColor.y+FragColor.z > 3){
	FragColor = vec4(1,0,0,1);
}

} 