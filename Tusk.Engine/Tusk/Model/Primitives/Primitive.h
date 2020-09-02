#pragma once

#include "Tusk/Renderer/Buffer.h"

namespace Tusk {
	enum class PrimitiveType {
		Cube = 0
	};

	class Primitive {
	public:
		virtual std::vector<Vertex> getVertices() = 0;
		virtual std::vector<uint32_t> getIndices() = 0;

		static Ref<Primitive> instantiate(PrimitiveType type);
	};
}