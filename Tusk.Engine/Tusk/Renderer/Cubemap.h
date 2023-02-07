#pragma once

namespace Tusk {
	class Cubemap {
	public:
		Cubemap() = default;

		virtual void bind() = 0;

		static Ref<Cubemap> create(const std::vector<std::string> faces);
	};
}