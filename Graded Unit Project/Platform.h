#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "loadTexture.h"
#include "drawableEntity.h"

#include "Model.h"
#include "Camera.h"

using namespace std;

class platform : DrawableEntity
{
private:
	glm::vec3 position;
	glm::vec3 scale;
	GLuint texture;

	Shader* shader;
	Model* myModel;
	Camera* camera;

public:
	platform(glm::vec3 position, glm::vec3 scale, GLuint texture) : position(position), scale(scale), texture(texture) {};
	
	void draw(SDL_Window* window);
	void update(SDL_Event _event);
	void init(void);
	//void Set_ShaderID(GLuint _id);
	//void getStack(std::stack<glm::mat4>* stack);
};