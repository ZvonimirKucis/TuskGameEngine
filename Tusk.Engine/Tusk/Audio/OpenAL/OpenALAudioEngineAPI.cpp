#include "tuskpch.h"

#include "OpenALAudioEngineAPI.h"

namespace Tusk{

	void OpenALAudioEngineAPI::init() {
		_openALDevice = alcOpenDevice(nullptr);
		if (!_openALDevice) {
			Logger::Fatal("No audio device detected!");
		}
		_openALContext = alcCreateContext(_openALDevice, nullptr);
		alcMakeContextCurrent(_openALContext);
	}

	OpenALAudioEngineAPI::~OpenALAudioEngineAPI() {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(_openALContext);

		alcCloseDevice(_openALDevice);
	}

}