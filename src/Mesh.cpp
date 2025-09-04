#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& pVertices, 
		   const std::vector<uint32_t>& pIndices, 
		   const std::vector<Texture2>& pTexture)
{
	init(pVertices, pIndices, pTexture);
}

void Mesh::init(const std::vector<Vertex>& pVertices,
				const std::vector<uint32_t>& pIndices,
				const std::vector<Texture2>& pTextures)
{
	mVAO.generate();
	mVAO.bind();
	mVBO.init(pVertices, GL_STATIC_DRAW);
	mVBOLayout.pushLayout(GL_FLOAT, 3);
	mVBOLayout.pushLayout(GL_FLOAT, 3);
	mVBOLayout.pushLayout(GL_FLOAT, 4);
	mVBOLayout.pushLayout(GL_FLOAT, 2);
	mVAO.addBuffer(mVBO, mVBOLayout);
	mEBO.init(pIndices.data(), pIndices.size());
	mTextures = pTextures;
	mVertices = pVertices;
	mIndices = pIndices;
}

void Mesh::setModelMatrix(const glm::mat4& pModelMatrix)
{
	mModelMatrix = pModelMatrix;
}

void Mesh::setViewMatrix(const glm::mat4& pViewMatrix)
{
	mViewMatrix = pViewMatrix;
}

void Mesh::setProjMatrix(const glm::mat4& pProjMatrix)
{
	mProjMatrix = pProjMatrix;
}

void Mesh::setMVP(const glm::mat4& pModelMatrix, 
				  const glm::mat4& pViewMatrix, 
				  const glm::mat4& pProjMatrix)
{
	mModelMatrix = pModelMatrix;
	mViewMatrix = pViewMatrix;
	mProjMatrix = pProjMatrix;
}

void Mesh::setVertices(const std::vector<Vertex>& pVertices)
{
	mVertices = pVertices;
}

void Mesh::setIndices(const std::vector<uint32_t>& pIndices)
{
	mIndices = pIndices;
}

void Mesh::setTextures(const std::vector<Texture2>& pTextures)
{
	mTextures = pTextures;
}

std::vector<Vertex>& Mesh::getVertices()
{
	return mVertices;
}

std::vector<uint32_t>& Mesh::getIndices()
{
	return mIndices;
}

std::vector<Texture2>& Mesh::getTextures()
{
	return mTextures;
}

glm::mat4 Mesh::getModelMatrix() const noexcept
{
	return mModelMatrix;
}

glm::mat4 Mesh::getViewMatrix() const noexcept
{
	return mViewMatrix;
}

glm::mat4 Mesh::getProjMatrix() const noexcept
{
	return mProjMatrix;
}

glm::mat4 Mesh::getMVP() const noexcept
{
	return mProjMatrix * mViewMatrix * mModelMatrix;
}

VAO Mesh::getVAO() const noexcept
{
	return mVAO;
}

VBO Mesh::getVBO() const noexcept
{
	return mVBO;
}

EBO Mesh::getEBO() const noexcept
{
	return mEBO;
}

VBOLayout Mesh::getVBOLayout() const noexcept
{
	return mVBOLayout;
}

void Mesh::draw(std::string_view pNameUniform, Shader& pShader)
{
	pShader.bind();
	pShader.setMatrixUniform4fv(pNameUniform, getMVP());
	mVAO.bind();
	mEBO.bind();
	glDrawElements(GL_TRIANGLES, mEBO.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::drawForModels(Shader& pShader)
{
	uint32_t diffuseNr = 0;
	uint32_t specularNr = 0;
	uint32_t heightNr = 0;
	uint32_t normalNr = 0;
	for (uint32_t i = 0; i < mTextures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = mTextures[i].getType();
		if (name == "texture_diffuse")
			number = std::to_string(++diffuseNr);
		else if (name == "texture_specular")
			number = std::to_string(++specularNr);
		else if (name == "texture_height")
			number = std::to_string(++heightNr);
		else if (name == "texture_normal")
			number = std::to_string(++normalNr);
		glUniform1i(pShader.getUniformLocation((name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, mTextures[i].getID());
	}

	mVAO.bind();
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
	mVAO.unbind();

	glActiveTexture(GL_TEXTURE0);
}
