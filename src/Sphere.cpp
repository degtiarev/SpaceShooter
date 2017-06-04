#include "Sphere.h"

Sphere::Sphere()
{

}

Sphere::~Sphere()
{
}



void Sphere::privateInit()
{
	myShader.initShaders("../shaders/phong");
	myShader.enable();

	glUniform3f(glGetUniformLocation(myShader.getProg(), "ObjColor"), 1.000f, 0.843f, 0.000f);
	glUniform3f(glGetUniformLocation(myShader.getProg(), "LightPosition"), -1.0, -100.0, 3.0);

	myShader.disable();


	matrix_ = glm::translate(matrix_, glm::vec3(-120, 120, -200));
}

void Sphere::privateRender()
{
	myShader.enable();
	glutSolidSphere(20.0, 150, 150);
	myShader.disable();


}

void Sphere::privateUpdate()
{


}

