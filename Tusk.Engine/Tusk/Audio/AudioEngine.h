#pragma once

#include "AudioEngineAPI.h"

namespace Tusk {

	class AudioEngine {
	public:
		static void init();



	private:
		static Scope<AudioEngineAPI> _audioEngineAPI;
	};

}