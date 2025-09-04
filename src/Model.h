#pragma once
#include <iostream>
#include <filesystem>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.h"
#include "Texture2.h"

class Model
{
public:
	Model() = default;
	Model(const std::filesystem::path& pPath);

	void load(const std::filesystem::path& pPath);
	void draw(std::string_view pNameUniform, Shader& pShader);

private:
	void loadModel(const std::filesystem::path& pPath);
	void processNode(aiNode* pNode, const aiScene* pScene);
	void processMesh(aiMesh* pMesh, const aiScene* pScene);
	void loadMaterialTextures(std::vector<Texture2>& pStrgToChange, aiMaterial* pMaterial, 
							  aiTextureType pTexType, std::string pTypeName);

private:
	std::vector<Mesh> mMeshes;
	std::vector<Texture2> mTexturesLoaded;
	std::filesystem::path mDirectory;
};

