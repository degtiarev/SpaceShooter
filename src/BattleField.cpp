#include "BattleField.hpp"


BattleField::BattleField()
{
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{
	auto glmVec = glm::vec3{};
	int CONST_SIZE_X = 32;
	int CONST_SIZE_Z = 512;
	float x_coord = 0.0;
	float z_coord = 0.0;
	// Create vertex arrays
	for (int i = 0; i < CONST_SIZE_X; i++) {

		for (int j = 0; j < CONST_SIZE_Z; j++) {

			x_coord = (i * 10) - 160;
			z_coord = (j*-10);

			this->vertexArray_.push_back(glm::vec3(x_coord, 0.0, z_coord));
		}

	}
	//set primitive restart values
	glPrimitiveRestartIndex(MAXUINT);
	//build index array
	for (int i = 0; i < CONST_SIZE_Z - 1; i++) {

		for (int j = 0; j < CONST_SIZE_X; j++) {

			this->indexArray_.push_back(j + CONST_SIZE_X + CONST_SIZE_X*i);
			this->indexArray_.push_back(j + CONST_SIZE_X*i);

		}
		this->indexArray_.push_back(MAXUINT);
	}
	int a = 7;

}

void BattleField::privateRender()
{
	// Render the battlefield
	//draw elements
	//glBegin(GL_TRIANGLES);
	//glVertex2f(3.67, 6.11);
	//glVertex2f(4.79, 6.15);
	//glVertex2f(4.61, 4.69);
	//glEnd();

	glEnable(GL_PRIMITIVE_RESTART);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
	//glDrawArrays(GL_POINTS, 0, vertexArray_.size());

	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
	glDrawElements(GL_QUAD_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_PRIMITIVE_RESTART);
}

void BattleField::privateUpdate()
{
}

