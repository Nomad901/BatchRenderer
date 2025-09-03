#pragma once
#include <iostream>
#include <filesystem>

#include "glad/glad.h"
#include "stb_image.h"

class Texture2
{
public:
	Texture2() = default;
	Texture2(const std::filesystem::path& pPath, std::string_view pUniformName);
	~Texture2();

	void init(const std::filesystem::path& pPath, std::string_view pUniformName);

	void bind(uint32_t pSlot = 0);
	void unbind();

	uint32_t getRendererId() const noexcept;
	std::string getUniformName() const noexcept;

private:
	int32_t mWidth, mHeight, mBPP;
	uint32_t mRendererID;
	uint8_t* mLocalBuffer;

	std::string mUniformName;
	std::filesystem::path mFilePath;
};

