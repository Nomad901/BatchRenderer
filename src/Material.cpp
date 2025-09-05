#include "Material.h"

Material::Material(glm::vec3 pAmbient, 
				   glm::vec3 pDiffuse, 
				   glm::vec3 pSpecular, 
				   GLint pDiffuseTex, 
				   GLint pSpecularTex)
{
	mAmbient = pAmbient;
	mDiffuse = pDiffuse;
	mSpecular = pSpecular;
	mDiffuseTex = pDiffuseTex;
	mSpecularTex = pSpecularTex;
}

void Material::sendToShader(Shader& pShader)
{
	pShader.setUniform3fv("material.ambient", mAmbient);
	pShader.setUniform3fv("material.diffuse", mDiffuse);
	pShader.setUniform3fv("material.specular", mSpecular);
	pShader.setUnifrom1i("material.diffuseTex", mDiffuseTex);
	pShader.setUnifrom1i("material.specularTex", mSpecularTex);
}
