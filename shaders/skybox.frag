#version 330 core
in vec2 TexCoords;

//out vec4 color;
//Texture sample
//uniform samplerCube skybox;

//void main()
//{   
//    color = texture(skybox,TexCoords);
//}

#version 120 
//http://www.c-jump.com/bcc/common/Talk3/OpenGL/Wk13_skybox/Wk13_skybox.html#W01_0060_skybox_shader_code 
out vec4 vFragColor; 
uniform samplerCube skybox; 
varying vec3 texCoord; 
void main() { 
gl_FragColor = texture(skybox, texCoord); 
}