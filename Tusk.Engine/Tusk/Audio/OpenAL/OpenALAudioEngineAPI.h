#pragma once

#include "Tusk/Audio/AudioEngineAPI.h"

#include <alc.h>

namespace Tusk {

	class OpenALAudioEngineAPI : public AudioEngineAPI {
	public:
		virtual ~OpenALAudioEngineAPI() override;

		virtual void init() override;

	private:
		ALCdevice* _openALDevice;
		ALCcontext* _openALContext;
	};

}