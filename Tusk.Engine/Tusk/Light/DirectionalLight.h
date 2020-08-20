#pragma once

#include <glm/glm.hpp>

namespace Tusk {
    struct DirectionalLight {
        glm::vec3 direction;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };
}