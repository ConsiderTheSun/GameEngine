#version 460 core

out vec4 FragColor;

in vec2 TexCoord;


uniform vec3 color;

uniform bool hasTexture;
uniform sampler2D textureData;

void main(void){


if(hasTexture){
	vec4 texColor = texture(textureData, TexCoord);
	if (texColor.a < 0.1) discard;
	FragColor = texColor * vec4(color, 1.0f);
}
else{
	FragColor = vec4(color, 1.0f);
}

} 