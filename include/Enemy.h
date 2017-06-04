

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader1.hpp"
#include "Model.h"


class Enemy : public SceneObject
{
public:
	Enemy(std::string type, float speed, int xBoundary, float startPos);
	~Enemy();


	int list_id;

	std::vector< std::vector<float>> getVertexArr();
	GLuint vertexbuffer;
	bool getEnemyStatus();// if enemy status is not active - erase enemy from the scene

	void setWeapon(std::string weapon);
	std::string getWeapon() const;

	glm::vec3 getPos() const;
	float getRadius() const;

	void createEnemy();
	bool shoot();
	int getAmmo();
	void setAmmo(int ammo);

	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;

	float speed_;
	float life_;
	float armor_;
	bool isActive_ = true;



protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

	glm::vec3 translateVec_;

private:
	std::string type_;

	std::string currentWeapon;
	int bulletAmount;
	float startPos_;


	bool checkFlag = false;
	float max_z = 50.0;
	float min_z = -150.0;

	float max_y = 10.0;
	float min_y = 0.0;

	int z_coord = 0;
	double y_coord = 0.0;

	GLuint textureName_;

	std::vector< std::vector<float>> vertexArray_; //vertex array
	std::vector< glm::vec3 > normalArray_; // normals array
	std::vector< glm::uint > indexArray_;  // index array

	std::vector<float> color_;

	int xBoundary_;
	int xPos_;

	std::shared_ptr<Model> myModel1;

};