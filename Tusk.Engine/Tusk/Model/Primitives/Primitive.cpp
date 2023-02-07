#include "tuskpch.h"

#include "Primitive.h"
#include "Cube.h"

namespace Tusk {
	Ref<Primitive> Primitive::instantiate(PrimitiveType type) {
		switch (type) {
			case PrimitiveType::Cube:
				return CreateRef<Cube>();
		}
	}
}