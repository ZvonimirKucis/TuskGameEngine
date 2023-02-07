#include "tuskpch.h"
#include "AudioEngineAPI.h"

#include "SoLoud/SoLoudAudioEngineAPI.h"

namespace Tusk {
	Scope<AudioEngineAPI> AudioEngineAPI::create() {
		return CreateScope<SoLoudAudioEngineAPI>();
	}
}