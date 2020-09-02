#pragma once

namespace Tusk {
	class AudioClip {
	public:
		virtual ~AudioClip() = default;

		virtual uint32_t getBuffer() = 0;

		static Ref<AudioClip> load(const std::string& path);
	};
}