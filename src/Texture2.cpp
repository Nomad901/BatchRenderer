#include "Texture2.h"

Texture2::Texture2(const std::filesystem::path& pPath, std::string_view pUniformName)
{
	init(pPath, pUniformName);
}

Texture2::~Texture2()
{
	glDeleteTextures(1, &mRendererID);
}

void Texture2::init(const std::filesystem::path& pPath, std::string_view pUniformName)
{
	mUniformName = pUniformName;
	mFilePath = pPath;
	stbi_set_flip_vertically_on_load(1);
	mLocalBuffer = stbi_load(pPath.string().c_str(), &mWidth, &mHeight, &mBPP, 4);

	glGenBuffers(1, &mRendererID);
	glBindTexture(GL_TEXTURE_2D, mRendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer);
	glBindBuffer(GL_TEXTURE_2D, 0);

	if (mLocalBuffer)
		stbi_image_free(mLocalBuffer);
}

void Texture2::bind(uint32_t pSlot)
{
	glActiveTexture(GL_TEXTURE0 + pSlot);
	glBindTexture(GL_TEXTURE_2D, mRendererID);
}

void Texture2::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Texture2::getRendererId() const noexcept
{
	return mRendererID;
}

std::string Texture2::getUniformName() const noexcept
{
	return mUniformName;
}
