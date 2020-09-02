#include "tuskpch.h"

#include <glm/glm.hpp>

#include "Model.h"
#include "Loader.h"

namespace Tusk {

	Model::Model(const std::string& path) {
		_mesh = Loader::loadModel(path);
	}

	Model::Model(const Ref<Primitive>& primitive) {
		_mesh = CreateRef<Mesh>(primitive->getVertices(), primitive->getIndices());
	}

    void Model::draw() {
		_mesh->draw();
    }
}