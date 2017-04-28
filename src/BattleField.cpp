#include "BattleField.hpp"
#include <SOIL.h>


BattleField::BattleField(int width_, int height_, int depth_)
{
	this->width_ = width_;
	this->height_ = height_;
	this->depth_ = depth_;
}

BattleField::BattleField()
{
}

BattleField::~BattleField()
{
}

int BattleField::getBattleWidth()
{
	return width_;
}

int BattleField::getBattleDepth()
{
	return depth_;
}

void BattleField::privateInit()
{
	auto glmVec = glm::vec3{};
	int CONST_SIZE_X = 32;
	int CONST_SIZE_Z = 512;
	float x_coord = 0.0;
	float z_coord = 0.0;
	// Create vertex array
	for (int i = 0; i < CONST_SIZE_Z; i++) {

		for (int j = 0; j < CONST_SIZE_X; j++) {

			x_coord = (j * 10) - 160;
			z_coord = (i*-10);

			this->vertexArray_.push_back(glm::vec3(x_coord, 0.0, z_coord));
		}

	}
	//Create texture array
	for (double i = 0; i < CONST_SIZE_Z; i++) {

		for (double j = 0; j < CONST_SIZE_X; j++) {

			x_coord = (j / (CONST_SIZE_X - 1));
			z_coord = (i / (CONST_SIZE_Z - 1));

			this->textureArray_.push_back(glm::vec2(x_coord, z_coord));
		}

	}
	//set primitive restart values
	glPrimitiveRestartIndex(MAXUINT);
	//build index array
	for (int i = 0; i < CONST_SIZE_Z - 1; i++) {

		for (int j = 0; j < CONST_SIZE_X; j++) {

			this->indexArray_.push_back((j + CONST_SIZE_X) + (CONST_SIZE_X*i));
			this->indexArray_.push_back(j + (CONST_SIZE_X*i));

		}
		this->indexArray_.push_back(MAXUINT);
	}
	int a = 7;
	//texture initiation
	int width, height;

	// check library linking!
	unsigned char* img = SOIL_load_image("../textures/colorMap2012.bmp", &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &textureName_);
	glBindTexture(GL_TEXTURE_2D, textureName_);

	if (!img)
		std::cout << "Not loaded" << sizeof(img) << std::endl;

	if (textureName_ == NULL) {

		printf("Error in download '%s'", SOIL_last_result());
	}
	else {
		std::cout << "Texture loaded: " << "size " << sizeof(img) << " height " << height << " width " << width << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

		SOIL_free_image_data(img);
		glBindTexture(GL_TEXTURE_2D, 0);
	}



	//second texture
	unsigned char* img2 = SOIL_load_image("../textures/heightMap2012.bmp", &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &secondTextureName_);
	glBindTexture(GL_TEXTURE_2D, secondTextureName_);

	if (!img)
		std::cout << "Not loaded" << sizeof(img2) << std::endl;

	if (secondTextureName_ == NULL) {

		printf("Error in download '%s'", SOIL_last_result());

	}
	else {
		std::cout << "Texture loaded: " << "size " << sizeof(img2) << " height " << height << " width " << width << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);

		SOIL_free_image_data(img2);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	shader_.initShaders("../Shaders/bfshader");
	shader_.enable();

	GLint texture1 = glGetUniformLocation(shader_.getProg(), "height");//fragment
	glUniform1i(texture1, 0);

	GLint texture2 = glGetUniformLocation(shader_.getProg(), "color");//vertex
	glUniform1i(texture2, 1);

	shader_.disable();

}

void BattleField::privateRender()
{

	shader_.enable();

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, secondTextureName_);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName_);



	glEnable(GL_PRIMITIVE_RESTART);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName_);

	// Render the battlefield
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoordPointer(2, GL_FLOAT, 0, &textureArray_[0]);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);

	glDrawElements(GL_QUAD_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_PRIMITIVE_RESTART);
	//texture	




	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);

	shader_.disable();

}

void BattleField::privateUpdate()
{
}

