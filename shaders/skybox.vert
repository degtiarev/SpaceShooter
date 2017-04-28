//#version 330 core
//layout (location = 0) in vec3 position;

//out vec3 TexCoords;

//uniform mat4 view;
//uniform mat4 projection;

//void main()
//{
//    vec4 pos = projection*view*vec4(position,1.0f);
//	gl_Position = pos.xyww;
//	TexCoords = position;
//}

#version 120 
//http://www.c-jump.com/bcc/common/Talk3/OpenGL/Wk13_skybox/Wk13_skybox.html#W01_0060_skybox_shader_code 
varying vec3 texCoord; 
void main() { 
texCoord = gl_MultiTexCoord0.xyz; gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 
}