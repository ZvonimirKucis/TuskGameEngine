#pragma once

namespace Tusk {

	class AudioEngineAPI {
	public:
		virtual ~AudioEngineAPI() = default;

		virtual void init() = 0;

		static Scope<AudioEngineAPI> create();
	};

}