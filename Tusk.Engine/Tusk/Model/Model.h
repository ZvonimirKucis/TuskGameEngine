#pragma once

#include <vector>

#include "Tusk/Renderer/Shader.h"
#include "Tusk/Renderer/Texture.h"

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Tusk {

    class Model {
    public:
        Model(const std::string& path);

        void draw(Ref<Shader> shader);

    private:
        void loadModel(const std::string& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Ref<Texture2D>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType customType);

    private:
        std::vector<Mesh> _meshes;
        std::vector<Ref<Texture2D>> _texturesLoaded;
        std::string _directory;
    };

}