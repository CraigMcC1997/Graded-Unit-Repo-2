#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "loadTexture.h"
#include "rt3d.h"
#include "rt3dObjLoader.h"

using namespace std;

class platform {
private:
	glm::vec3 position;
	GLuint myShaderProgram;
	GLuint meshObject;
	GLuint texture;
	GLuint size;
	GLuint meshIndexCount = 0;
	stack<glm::mat4> mvStack;
	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;
	rt3d::materialStruct material;

public:
	platform(glm::vec3 position) : position(position) {};
	glm::vec3 getPosition();
	void draw(std::stack<glm::mat4> *_mvStack);
	void init(void);
	void Set_ShaderID(GLuint _id);
};