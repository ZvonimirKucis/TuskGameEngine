#pragma once

namespace Tusk {

	class AudioEngineAPI {
	public:
		virtual ~AudioEngineAPI() = 0;

		virtual void init() = 0;

		static Scope<AudioEngineAPI> create();
	};

}