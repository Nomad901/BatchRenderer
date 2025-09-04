#include "Mesh.h"

void Mesh::init(const std::vector<Vertex>& pVertices, 
				const std::vector<uint32_t>& pIndices)
{
	mVAO.bind();
	mVBO.init(pVertices, GL_STATIC_DRAW);
	mEBO.init(pIndices.data(), pIndices.size());
	mVBOLayout.pushLayout(GL_FLOAT, 3);
	mVBOLayout.pushLayout(GL_FLOAT, 4);
	mVBOLayout.pushLayout(GL_FLOAT, 2);
	mVBOLayout.pushLayout(GL_FLOAT, 1);
	mVAO.addBuffer(mVBO, mVBOLayout);
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

std::vector<Vertex>& Mesh::getVertices()
{
	return mVertices;
}

std::vector<uint32_t>& Mesh::getIndices()
{
	return mIndices;
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
