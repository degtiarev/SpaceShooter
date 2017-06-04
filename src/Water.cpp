#include "Water.h"

Water::Water(std::shared_ptr<Skybox> skybox)
{

	width_ = 64;
	length_ = 128;
	waveTime_ = 0.5f;
	waveWidth_ = 0.6f;
	waveHeight_ = 1.0f;
	waveFreq_ = 0.1f;
	skybox_ = skybox;
}

Water::~Water()
{
}

void Water::privateInit()
{
	matrix_ = glm::translate(matrix_, getPos());

	createArrays();

	int width, height;

	unsigned char* img = SOIL_load_image("../textures/waterT.jpg", &width, &height, 0, SOIL_LOAD_RGB);//color

	glGenTextures(1, &waterTexture_);
	glBindTexture(GL_TEXTURE_2D, waterTexture_);

	if (!img)
		std::cout << "Not loaded" << sizeof(img) << std::endl;

	if (waterTexture_ == NULL) {

		printf("Error in download '%s'", SOIL_last_result());
	}
	else {
		std::cout << "Texture loaded, water: " << "size " << sizeof(img) << " height " << height << " width " << width << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

		SOIL_free_image_data(img);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	shader_.initShaders("../Shaders/water");
	shader_.enable();
	//glUniform3f(glGetUniformLocation(shader_.getProg(), "ObjColor"), 0.0, 0.0, 1.0);
	//glUniform1f(glGetUniformLocation(shader_.getProg(), "waveTime"), waveTime_);
	//glUniform1f(glGetUniformLocation(shader_.getProg(), "waveWidth"), 0.7f);
	//glUniform1f(glGetUniformLocation(shader_.getProg(), "waveHeight"), 0.2f);
	glUniform1i(glGetUniformLocation(shader_.getProg(), "skybox"), 0);
	//glUniform1i(glGetUniformLocation(shader_.getProg(), "waterTex"), 1);
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveTime"), waveTime_);
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveWidth"), waveWidth_);
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveHeight"), waveHeight_);
	//shaderInit(shader_, 0);
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -52.0f, -70.0f));
	shader_.disable();




}

void Water::privateRender()
{
	//shader_.enable();
	//glEnableClientState(GL_VERTEX_ARRAY); // enable vertex arrays
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]); // set vertex pointer
	//glTexCoordPointer(2, GL_FLOAT, 0, &textureArray_[0]);
	//glEnable(GL_PRIMITIVE_RESTART);
	//glDrawElements(GL_QUAD_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);

	//glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays 
	//glDisable(GL_PRIMITIVE_RESTART);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//shader_.disable();
	shader_.enable();
	glActiveTexture(GL_TEXTURE0);

	//glActiveTexture(GL_TEXTURE1);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, waterTexture_);

	shaderRender(skybox_, indexArray_);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_CUBE_MAP);

	//glActiveTexture(GL_TEXTURE1);
	//glDisable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, 0);
	shader_.disable();
}

void Water::privateUpdate()
{
	/*shader_.enable();
	waveTime_ += waveFreq_;
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveTime"), waveTime_);*/
	//pos_ += step_;
	waveTime_ += waveFreq_;

	shader_.enable();
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveTime"), waveTime_);
	shader_.disable();
	// Translate the water into a loop
	//if (pos_.z < length_ * 10)
	//{
	//	matrix_ = glm::translate(matrix_, getStep());
	//}
	//else
	//{
	//	pos_.z = -length_ * 10.0f;
	//	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -length_*20.0f));
	//}
	//shader_.disable();
}

glm::vec3 Water::getPos() const
{
	return pos_;
}

glm::vec3 Water::getStep() const
{
	return step_;
}

void Water::createArrays()
{
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
}

void Water::shaderRender(std::shared_ptr<Skybox> skybox, std::vector<unsigned int> indexArray)
{
	auto tex = skybox->getTextures();
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glEnable(GL_PRIMITIVE_RESTART);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
	glDrawElements(GL_QUAD_STRIP, indexArray.size(), GL_UNSIGNED_INT, &indexArray[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_PRIMITIVE_RESTART);
}

void Water::setZpos(float zpos)
{
	this->matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -zpos));
}
