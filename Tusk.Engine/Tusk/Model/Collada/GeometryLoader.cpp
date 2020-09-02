#include "tuskpch.h"

#include "GeometryLoader.h"
#include "Tusk/Model/Utils/Utils.h"

namespace Tusk {

	GeometryLoader::GeometryLoader(const pugi::xml_node& geometryNode) {
		_meshData = geometryNode.child("geometry").child("mesh");
	}

	GeometryLoader::GeometryLoader(const pugi::xml_node& geometryNode, const std::vector<Ref<VertexSkin>>& vertexSkin) {
		_meshData = geometryNode.child("geometry").child("mesh");
		_vertexSkin = vertexSkin;
	}

	Ref<Mesh> GeometryLoader::loadMesh() {
		extractMeshData();
		Utils::calculateTangentSpace(_vertices);
		return CreateRef<Mesh>(_vertices, _indices);
	}

	Ref<Mesh> GeometryLoader::loadAnimatedMesh() {
		extractAnimatedMeshData();
		Utils::calculateTangentSpace(_vertices);
		return CreateRef<Mesh>(_vertices, _indices);
	}

	void GeometryLoader::extractMeshData() {
		std::vector<glm::vec3> positions = readPositions();
		std::vector<glm::vec3> normals = readNormals();
		std::vector<glm::vec2> textureCoords = readTextureCoords();

		pugi::xml_node indicesData = _meshData.child("polylist").child("p");
		std::vector<std::string> indicesDataVector = Utils::split(indicesData.child_value(), ' ');
		uint32_t typeCount = std::distance(_meshData.child("polylist").children("input").begin(), _meshData.child("polylist").children("input").end());

		for (uint32_t i = 0; i < indicesDataVector.size() / typeCount; i++) {
			Vertex vertex;
			vertex.position = positions[std::stoi(indicesDataVector[i * typeCount])];
			vertex.normal = normals[std::stoi(indicesDataVector[i * typeCount + 1])];
			vertex.texCoords = textureCoords[std::stoi(indicesDataVector[i * typeCount + 2])];
			
			_vertices.push_back(vertex);
			_indices.push_back(i);
		}
	}

	void GeometryLoader::extractAnimatedMeshData() {
		std::vector<glm::vec3> positions = readPositions();
		std::vector<glm::vec3> normals = readNormals();
		std::vector<glm::vec2> textureCoords = readTextureCoords();

		pugi::xml_node indicesData = _meshData.child("polylist").child("p");
		std::vector<std::string> indicesDataVector = Utils::split(indicesData.child_value(), ' ');
		uint32_t typeCount = std::distance(_meshData.child("polylist").children("input").begin(), _meshData.child("polylist").children("input").end());

		for (uint32_t i = 0; i < indicesDataVector.size() / typeCount; i++) {
			Vertex vertex;
			vertex.position = positions[std::stoi(indicesDataVector[i * typeCount])];
			vertex.normal = normals[std::stoi(indicesDataVector[i * typeCount + 1])];
			vertex.texCoords = textureCoords[std::stoi(indicesDataVector[i * typeCount + 2])];

			std::vector<VertexSkinData> skinData = _vertexSkin[std::stoi(indicesDataVector[i * typeCount])]->getSkinData();
			glm::vec3 jointIndices = glm::vec3();
			glm::vec3 weights = glm::vec3();
			for (uint32_t j = 0; j < skinData.size(); j++) {
				jointIndices[j] = skinData[j].jointID;
				weights[j] = skinData[j].weight;
			}

			vertex.jointIndices = jointIndices;
			vertex.weights = weights;

			_vertices.push_back(vertex);
			_indices.push_back(i);
		}
	}

	std::vector<glm::vec3> GeometryLoader::readPositions() {
		std::vector<glm::vec3> positions;

		std::string positionsId = _meshData.child("vertices").child("input").attribute("source").as_string();
		positionsId.erase(0, 1);
		pugi::xml_node positionsData = _meshData.find_child_by_attribute("source", "id", positionsId.c_str()).child("float_array");
		
		uint32_t count = std::stoi(positionsData.attribute("count").value());
		std::vector<std::string> positionDataVector = Utils::split(positionsData.child_value(), ' ');

		for (int i = 0; i < count / 3; i++) {
			float x = std::stof(positionDataVector[i * 3]);
			float y = std::stof(positionDataVector[i * 3 + 1]);
			float z = std::stof(positionDataVector[i * 3 + 2]);
			
			glm::vec4 position = glm::vec4(x, y, z, 1);
			position = Utils::correction * position;
			positions.push_back(glm::vec3(position.x, position.y, position.z));
		}

		return positions;
	}

	std::vector<glm::vec3> GeometryLoader::readNormals() {
		std::vector<glm::vec3> normals;

		std::string normalsId = _meshData.child("polylist").find_child_by_attribute("input", "semantic", "NORMAL").attribute("source").as_string();
		normalsId.erase(0, 1);
		pugi::xml_node normalsData = _meshData.find_child_by_attribute("source", "id", normalsId.c_str()).child("float_array");

		uint32_t count = std::stoi(normalsData.attribute("count").value());
		std::vector<std::string> normalDataVector = Utils::split(normalsData.child_value(), ' ');

		for (int i = 0; i < count / 3; i++) {
			float x = std::stof(normalDataVector[i * 3]);
			float y = std::stof(normalDataVector[i * 3 + 1]);
			float z = std::stof(normalDataVector[i * 3 + 2]);

			glm::vec4 normal = glm::vec4(x, y, z, 0);
			normal = Utils::correction * normal;
			normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
		}

		return normals;
	}

	std::vector<glm::vec2> GeometryLoader::readTextureCoords() {
		std::vector<glm::vec2> textureCoords;

		std::string texCoordsId = _meshData.child("polylist").find_child_by_attribute("input", "semantic", "TEXCOORD").attribute("source").as_string();
		texCoordsId.erase(0, 1);
		pugi::xml_node texCoordsData = _meshData.find_child_by_attribute("source", "id", texCoordsId.c_str()).child("float_array");

		uint32_t count = std::stoi(texCoordsData.attribute("count").value());
		std::vector<std::string> texCoordsVector = Utils::split(texCoordsData.child_value(), ' ');

		for (int i = 0; i < count / 2; i++) {
			float s = std::stof(texCoordsVector[i * 2]);
			float t = std::stof(texCoordsVector[i * 2 + 1]);

			glm::vec2 textureCoord = glm::vec2(s, t);
			textureCoords.push_back(textureCoord);
		}

		return textureCoords;
	}

	GeometryLoader::~GeometryLoader() {
		_vertices.clear();
		_indices.clear();
	}
}