#pragma once

#include <vector>

#include "Mesh.h"
#include "Primitives/Primitive.h"

namespace Tusk {

    class Model {
    public:
        Model(const std::string& path);
        Model(const Ref<Primitive>& primitive);

        void draw();

    private:
        Ref<Mesh> _mesh;
    };

}