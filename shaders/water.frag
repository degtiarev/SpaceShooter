#version 130
uniform samplerCube skybox;
uniform sampler2D waterTex;

varying vec3 norm;
varying vec3 viewVec;

void main () 
{

	//vec3 ref = reflect(viewVec, norm);

	//vec4 colorFog = texture(skybox, ref);
	//gl_FragColor = 	colorFog;

    vec3 ref = reflect(viewVec, norm);

    gl_FragColor = texture(skybox, ref);
	
}