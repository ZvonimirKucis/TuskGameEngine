#include "tuskpch.h"

#include "ColladaLoader.h"
#include <pugixml.hpp>

#include "GeometryLoader.h"

namespace Tusk {

	Ref<Mesh> ColladaLoader::loadModel(const std::string& path) {
		Logger::Log("%s", path.c_str());
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(path.c_str());
		if (!result)
			Logger::Fatal("Unable to parse DAE file: %s, description: %s", path.c_str(), result.description());
		
		pugi::xml_node rootNode = doc.child("COLLADA");

		Scope<GeometryLoader> gl = CreateScope<GeometryLoader>(rootNode.child("library_geometries"));
		
		return gl->loadMesh();
	}

}