#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <unordered_map>

#include "glm.hpp"
#include "glad/glad.h"

class Shader
{
public:
	Shader() = default;
	Shader(const std::filesystem::path& pPathVertex,
		   const std::filesystem::path& pPathFragment);
	~Shader();

	void init(const std::filesystem::path& pPathVertex,
			  const std::filesystem::path& pPathFragment);

	void bind();
	void unbind();

private:
	uint32_t createShaders(std::string_view pFragmentSource, std::string_view pVertexSource);
	uint32_t compileShaders(GLuint pType, const std::string& pStr);
	std::string parsePath(const std::filesystem::path& pPath);
	GLuint getUniformLocation(std::string_view pName);

private:
	uint32_t mShaderID;
	std::filesystem::path mPathVertex, mPathFragment;
	std::unordered_map<std::string, GLuint> mStorageLocations;
};

