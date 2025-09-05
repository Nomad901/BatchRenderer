#pragma once
#include <iostream>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

class Material
{
public:
	Material(glm::vec3 pAmbient,
			 glm::vec3 pDiffuse,
			 glm::vec3 pSpecular,
			 GLint pDiffuseTex,
			 GLint pSpecularTex);

	void sendToShader(Shader& pShader);

private:
	glm::vec3 mAmbient;
	glm::vec3 mDiffuse;
	glm::vec3 mSpecular;
	GLint mDiffuseTex;
	GLint mSpecularTex;

};

