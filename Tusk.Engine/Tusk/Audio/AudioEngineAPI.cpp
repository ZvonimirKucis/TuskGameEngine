#include "tuskpch.h"

#include "AudioEngineAPI.h"

#include "OpenAL/OpenALAudioEngineAPI.h"

namespace Tusk {
	Scope<AudioEngineAPI> AudioEngineAPI::create() {
		return CreateScope<OpenALAudioEngineAPI>();
	}
}