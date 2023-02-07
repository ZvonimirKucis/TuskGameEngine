#pragma once

#include "Primitive.h"

namespace Tusk {
	class Cube : public Primitive {
	public:
		Cube() = default;

		virtual std::vector<Vertex> getVertices() override;
		virtual std::vector<uint32_t> getIndices() override;
	};
}