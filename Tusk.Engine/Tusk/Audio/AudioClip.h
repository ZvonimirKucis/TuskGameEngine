#pragma once

namespace Tusk {
	class AudioClip {
	public:
		virtual ~AudioClip() = default;

		virtual void play() = 0;

		static Ref<AudioClip> load(const std::string& path);
	};
}