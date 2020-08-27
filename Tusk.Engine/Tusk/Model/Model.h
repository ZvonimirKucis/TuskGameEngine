#pragma once

#include <vector>

#include "Mesh.h"

namespace Tusk {

    class Model {
    public:
        Model(const std::string& path);

        void draw();

    private:
        Ref<Mesh> _mesh;
    };

}