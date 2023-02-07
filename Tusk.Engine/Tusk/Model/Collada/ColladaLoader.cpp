#include "tuskpch.h"

#include "ColladaLoader.h"
#include <pugixml.hpp>

#include "GeometryLoader.h"
#include "SkinLoader.h"
#include "SkeletonLoader.h"
#include "AnimationLoader.h"

namespace Tusk {

	Ref<Mesh> ColladaLoader::loadModel(const std::string& path) {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(path.c_str());
		if (!result)
			Logger::Fatal("Unable to parse DAE file: %s, description: %s", path.c_str(), result.description());
		
		pugi::xml_node rootNode = doc.child("COLLADA");

		Scope<GeometryLoader> geometryLoader = CreateScope<GeometryLoader>(rootNode.child("library_geometries"));
		
		return geometryLoader->loadMesh();
	}

	Ref<Mesh> ColladaLoader::loadAnimatedModel(const std::string& path, uint32_t maxJoints, Ref<Joint>& rootJoint, uint32_t* jointCount) {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(path.c_str());
		if (!result)
			Logger::Fatal("Unable to parse DAE file: %s, description: %s", path.c_str(), result.description());

		pugi::xml_node rootNode = doc.child("COLLADA");

		Scope<SkinLoader> skinLoader = CreateScope<SkinLoader>(rootNode.child("library_controllers"), maxJoints);
		Scope<SkeletonLoader> skeletonLoader = CreateScope<SkeletonLoader>(rootNode.child("library_visual_scenes"), skinLoader->extractJointNames());
		rootJoint = skeletonLoader->extractBoneData();
		*jointCount = skeletonLoader->getJointCount();

		Scope<GeometryLoader> geometryLoader = CreateScope<GeometryLoader>(rootNode.child("library_geometries"), skinLoader->extractSkinData());

		return geometryLoader->loadAnimatedMesh();
	}

	Ref<Animation> ColladaLoader::loadAnimation(const std::string& path) {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(path.c_str());
		if (!result)
			Logger::Fatal("Unable to parse DAE file: %s, description: %s", path.c_str(), result.description());

		pugi::xml_node rootNode = doc.child("COLLADA");

		pugi::xml_node animNode = rootNode.child("library_animations");
		//pugi::xml_node jointsNode = rootNode.child("library_visual_scenes");
		Scope<AnimationLoader> animationLoader = CreateScope<AnimationLoader>(animNode);

		return animationLoader->extractAnimation();
	}

}