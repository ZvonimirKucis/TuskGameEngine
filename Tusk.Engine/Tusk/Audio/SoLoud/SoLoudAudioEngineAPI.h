#pragma once

#include "Tusk/Audio/AudioEngineAPI.h"

#include <soloud.h>

namespace Tusk {

	class SoLoudAudioEngineAPI : public AudioEngineAPI {
	public:
		virtual ~SoLoudAudioEngineAPI() override;

		virtual void init() override;

		SoLoud::Soloud* getEngine() { return _soloudEngine; }

	private:
		SoLoud::Soloud* _soloudEngine;
	};

}