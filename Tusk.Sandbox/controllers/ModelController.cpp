#include "ModelController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {
	Ref<AudioClip> audioClip;

	void ModelController::onCreate() {
		audioClip = AudioClip::load("assets/sound/africa-toto.wav");
		/*auto& source = getComponent<AudioSourceComponent>().source;
		source->setMaxDistance(50.0f);
		source->setVolume(0.3f);
		source->setLooping(true);
		source->play(audioClip);*/
	}

	void ModelController::onDestroy() {
	}

	void ModelController::onUpdate(float deltaTime) {
		auto& transform = getComponent<Tusk::TransformComponent>().transform;
		auto rot = transform.getRotation();
		rot.y -= deltaTime * 90.0f;
		transform.setRotation(rot);
	}
}