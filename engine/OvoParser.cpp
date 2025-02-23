
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/packing.hpp>

#include "OvoParser.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Enums.h"
#include "Texture.h"

	
void OvoParser::parseFile(const std::string& fileName) {
	const std::filesystem::path file_path = m_directory / fileName;
	std::ifstream input{ file_path.string(), std::ios::binary };

	bool isFirstTimeNodeEncountered = true;
	while (input) {
		// sanity check
		if (!input.good()) break;

		// parse chunk header first
		int chunkId = 0, chunkSize = 0;
		input.read(reinterpret_cast<char*>(&chunkId), sizeof(std::int32_t));
		input.read(reinterpret_cast<char*>(&chunkSize), sizeof(std::int32_t));

		// 1. If we find the [root] node in the OVO, then we must recursively build the graph scene with the following chunks
		if (static_cast<OvObjectType>(chunkId) == OvObjectType::NODE && isFirstTimeNodeEncountered) {
			// move back input iterator by 8 bytes, since we parsed the header which is 8 bytes (we are reparsing it in parseNode())
			input.seekg(input.tellg() - static_cast<std::streamoff>(sizeof(std::int32_t) * 2));

			// [root] node encountered: load file starting from this chunk to a buffer and build the scene graph hierarchy
			std::size_t position = 0;
			m_root = std::move(parseNode(loadFileIntoMemory(input), position));
			isFirstTimeNodeEncountered = false;

			return;
		}

		// 2. Otherwise, we haven't encountered a root node yet, so we parse the file "normally" without considering the nodes
		dispatchChunkParsing(chunkId, chunkSize, input);
	}
}

std::unique_ptr<Node> OvoParser::getRoot() {
	return std::move(m_root); // transfer ownership
}

std::vector<std::shared_ptr<Material>> OvoParser::getMaterials() const {
	return m_materials;
}

std::vector<std::shared_ptr<Texture>> OvoParser::getTextures() const {
	return m_textures;
}

std::unique_ptr<Node> OvoParser::parseNode(const std::vector<char>& buffer, std::size_t& position) {
	std::size_t updatedStartPos = position;
	if (position >= buffer.size()) return nullptr;
	const std::pair chunkHeader = parseChunkHeader(buffer, position);

	/****************************************/
	// CHUNK: NODE PART BEGIN
	/****************************************/
	// Node name
	std::size_t length = std::strlen(buffer.data() + position);
	std::string nodeName{ buffer.data() + position, buffer.data() + position + length };
	position += length + 1;

	// Node matrix
	glm::mat4 matrix;
	std::memcpy(&matrix, buffer.data() + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

	// Number of children
	std::uint32_t numChildren;
	std::memcpy(&numChildren, buffer.data() + position, sizeof(std::uint32_t));
	position += sizeof(std::uint32_t);

	// Optional target name (Ignored)
	std::size_t targetLength = std::strlen(buffer.data() + position);
	//std::string targetName{ buffer.data() + position, buffer.data() + position + targetLength };
	position += targetLength + 1;
	/****************************************/
	// CHUNK: NODE PART END
	/****************************************/



	/****************************************/
	// CHUNK: REST (e.g. Mesh, Light...) BEGIN
	/****************************************/
	std::unique_ptr<Node> currentNode;
	switch (static_cast<OvObjectType>(chunkHeader.first)) {
	case OvObjectType::NODE:
		currentNode = std::make_unique<Node>("Node", nodeName);
		break;

	case OvObjectType::LIGHT: {
		std::byte lightSubtype;
		std::memcpy(&lightSubtype, buffer.data() + position, sizeof(std::byte));
		position += sizeof(std::byte);

		if (static_cast<OvLightSubType>(lightSubtype) == OvLightSubType::OMNI) {
			currentNode = std::make_unique<PointLight>(nodeName);
			parseLight<OvLightSubType::OMNI>(buffer, position, dynamic_cast<PointLight*>(currentNode.get()));
		}
		else if (static_cast<OvLightSubType>(lightSubtype) == OvLightSubType::DIRECTIONAL) {
			currentNode = std::make_unique<DirectionalLight>(nodeName);
			parseLight<OvLightSubType::DIRECTIONAL>(buffer, position, dynamic_cast<DirectionalLight*>(currentNode.get()));
		}
		else {
			currentNode = std::make_unique<SpotLight>(nodeName);
			parseLight<OvLightSubType::SPOT>(buffer, position, dynamic_cast<SpotLight*>(currentNode.get()));
		}
		break;
	}

	case OvObjectType::MESH: [[fallthrough]];
	case OvObjectType::SKINNED: {
		currentNode = std::make_unique<Mesh>(nodeName);
		if (static_cast<OvObjectType>(chunkHeader.first) == OvObjectType::SKINNED)
			parseMesh(buffer, position, true, dynamic_cast<Mesh*>(currentNode.get()));
		else
			parseMesh(buffer, position, false, dynamic_cast<Mesh*>(currentNode.get()));
		break;
	}

	default: return nullptr;
	}

	currentNode->set_local_matrix(matrix);
	for (std::uint32_t i = 0; i < numChildren; ++i) {
		std::unique_ptr<Node> childNode = parseNode(buffer, position);
		if (childNode != nullptr)
			currentNode->add_child(std::move(childNode));
	}

	return std::move(currentNode);
	/****************************************/
	// CHUNK: REST (e.g. Mesh, Light...) END
	/****************************************/
}


std::vector<char> OvoParser::loadFileIntoMemory(std::ifstream& file) {
	const std::streampos startPosition = file.tellg();

	// copy content of file to buffer only starting from [root] node chunk, to build the scene graph hierarchy
	file.seekg(0, std::ios::end);
	const std::streampos endPosition = file.tellg();
	const std::streamsize fileSize = endPosition - startPosition;

	std::vector<char> buffer(fileSize);
	file.seekg(startPosition);
	file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

	return buffer;
}

void OvoParser::dispatchChunkParsing(int chunkId, int chunkSize, std::ifstream& input) {
	// Read chunkSize from file, save in buffer
	std::vector<char> buffer(chunkSize);
	input.read(buffer.data(), buffer.size());

	std::size_t chunk_position = 0;

	// Dispatch depending on the chunkId
	switch (static_cast<OvObjectType>(chunkId)) {
	case OvObjectType::OBJECT:
		parseVersion(buffer, chunk_position);
		break;

	case OvObjectType::MATERIAL:
		parseMaterial(buffer, chunk_position);
		break;

	case OvObjectType::BONE:
		parseBones(buffer, chunk_position);
		break;

		// The rest is parsed in parseNode(), since the rest is related to Nodes.
	default:
		//std::cerr << "OvoParser::dispatchChunkParsing: Object Type not found!\n";
		return;
	}
}

std::pair<int, int> OvoParser::parseChunkHeader(const std::vector<char>& buffer, std::size_t& position) {
	std::size_t chunkId;
	std::memcpy(&chunkId, buffer.data() + position, sizeof(std::uint32_t));
	position += sizeof(std::uint32_t);

	// Chunk size
	std::size_t chunkSize;
	std::memcpy(&chunkSize, buffer.data() + position, sizeof(std::uint32_t));
	position += sizeof(std::uint32_t);

	return std::pair{ chunkId, chunkSize };
}

void OvoParser::parseVersion(const std::vector<char>& buffer, std::size_t& position) {
	// Ignored
	// std::size_t versionId = 0;
	// std::memcpy(&versionId, buffer.data() + position, sizeof(std::uint32_t));
	position += sizeof(std::uint32_t);
}

void OvoParser::parseMaterial(const std::vector<char>& buffer, std::size_t& position) {
	// Material name
	std::size_t length = std::strlen(buffer.data() + position);
	std::string materialName{ buffer.data() + position, buffer.data() + position + length };
	position += length + 1;

	// Material term colors: Emissive
	glm::vec3 emissiveTerm;
	std::memcpy(&emissiveTerm, buffer.data() + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// Material term colors: Albedo
	glm::vec3 albedoTerm;
	std::memcpy(&albedoTerm, buffer.data() + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// Roughness factor
	float roughness;
	std::memcpy(&roughness, buffer.data() + position, sizeof(float));
	position += sizeof(float);

	// Metalness factor
	float metalness;
	std::memcpy(&metalness, buffer.data() + position, sizeof(float));
	position += sizeof(float);

	// alpha factor
	float alpha;
	std::memcpy(&alpha, buffer.data() + position, sizeof(float));
	position += sizeof(float);

	// Shared material, because multiple Meshes might refer to the same Material.
	auto material = std::make_shared<Material>(materialName);

	// texture filename albedo
	std::size_t albedoTextureFilenameLen = std::strlen(buffer.data() + position);
	std::string albedoTextureName{ buffer.data() + position, buffer.data() + position + albedoTextureFilenameLen };
	position += albedoTextureFilenameLen + 1;
	if (albedoTextureName != "[none]") {
		auto texture = std::make_shared<Texture>(albedoTextureName);
		texture->setTextId();
		material->setTexture(texture);
		m_textures.push_back(texture);
	}


	material->setMaterialSettings(glm::vec4{ emissiveTerm, 1.0f }, (1 - sqrt(roughness)) * 128,
		glm::vec4{ albedoTerm * 0.2f, 1.0f }, glm::vec4{ albedoTerm * 0.6f, 1.0f },
		glm::vec4{ albedoTerm * 0.4f, 1.0f }, alpha
	);
	m_materials.push_back(material);

	// Normal map filename -- Ignored
	std::size_t normalMapFilenameLen = std::strlen(buffer.data() + position);
	// std::string normalMapName{ buffer.data() + position, buffer.data() + position + normalMapFilenameLen };
	position += normalMapFilenameLen + 1;

	// Height map filename -- Ignored
	std::size_t heightMapFilenameLen = std::strlen(buffer.data() + position);
	// std::string heightMapFilename{ buffer.data() + position, buffer.data() + position + heightMapFilenameLen };
	position += heightMapFilenameLen + 1;

	// Roughness map filename -- Ignored
	std::size_t roughnessMapFilenameLen = std::strlen(buffer.data() + position);
	// std::string roughnessMapFilename{ buffer.data() + position, buffer.data() + position + roughnessMapFilenameLen };
	position += roughnessMapFilenameLen + 1;

	// Metalness map filename -- Ignored
	std::size_t metalnessMapFilenameLen = std::strlen(buffer.data() + position);
	// std::string metalnessMapFilename{ buffer.data() + position, buffer.data() + position + metalnessMapFilenameLen };
	position += metalnessMapFilenameLen + 1;
}

void OvoParser::parseMesh(const std::vector<char>& buffer, std::size_t& position, bool isSkinned, Mesh* mesh) {
	// Node part: Parsed in parseNode()

	// Mesh Subtype
	std::byte meshSubType;
	std::memcpy(&meshSubType, buffer.data() + position, sizeof(std::byte));
	position += sizeof(std::byte);

	// Material Name
	std::size_t materialNameLen = std::strlen(buffer.data() + position);
	std::string materialName{ buffer.data() + position, buffer.data() + position + materialNameLen };
	position += materialNameLen + 1;

	// Mesh Sphere Radius
	float radius;
	std::memcpy(&radius, buffer.data() + position, sizeof(float));
	position += sizeof(float);

	// Bounding box min corner
	glm::vec3 boundingBoxMinCorner;
	std::memcpy(&boundingBoxMinCorner, buffer.data() + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// Bounding box max corner
	glm::vec3 boundingBoxMaxCorner;
	std::memcpy(&boundingBoxMaxCorner, buffer.data() + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// skipped Optional physics properties:
	bool hasPhysics;
	memcpy(&hasPhysics, buffer.data() + position, sizeof(bool));
	position += sizeof(bool);

	// Skipped part
	if (hasPhysics) parsePhysicsProperties(buffer, position);

	// Number of LODs
	std::uint32_t numOfLODs;
	std::memcpy(&numOfLODs, buffer.data() + position, sizeof(std::uint32_t));
	position += sizeof(std::uint32_t);

	// Vertices per LOD
	std::vector<LodData> allLodInfo;
	std::vector<std::uint32_t> numOfVerticesPerLOD(numOfLODs);
	for (auto& currentLod : numOfVerticesPerLOD) {
		LodData lodInfo;

		// Vertices number for current LOD
		std::uint32_t numOfVertices;
		std::memcpy(&numOfVertices, buffer.data() + position, sizeof(std::uint32_t));
		currentLod = numOfVertices;
		position += sizeof(std::uint32_t);
		lodInfo.numVertices = numOfVertices;

		// Faces number for current LOD
		std::uint32_t numOfFaces;
		std::memcpy(&numOfFaces, buffer.data() + position, sizeof(std::uint32_t));
		position += sizeof(std::uint32_t);
		lodInfo.numFaces = numOfFaces;

		// Vertex data for each vertex for current LOD
		for (std::uint32_t i = 0; i < numOfVertices; ++i) {
			VertexData vertexData;

			// Vertex coordinates
			glm::vec3 vertexCoords;
			std::memcpy(&vertexCoords, buffer.data() + position, sizeof(glm::vec3));
			position += sizeof(glm::vec3);
			vertexData.vertex = vertexCoords;

			// Vertex normal coordinates
			std::uint32_t vertexNormal;
			std::memcpy(&vertexNormal, buffer.data() + position, sizeof(std::uint32_t));
			position += sizeof(std::uint32_t);
			vertexData.normal = glm::unpackSnorm3x10_1x2(vertexNormal);;

			// Texture coordinates
			std::uint32_t textureCoords;
			std::memcpy(&textureCoords, buffer.data() + position, sizeof(std::uint32_t));
			position += sizeof(std::uint32_t);
			vertexData.textureData = glm::unpackHalf2x16(textureCoords);

			// Tangent vector
			std::uint32_t tangentVec;
			std::memcpy(&tangentVec, buffer.data() + position, sizeof(std::uint32_t));
			position += sizeof(std::uint32_t);
			vertexData.tangentData = glm::unpackSnorm3x10_1x2(tangentVec);

			lodInfo.vertices.push_back(vertexData);
		}

		// Faces data for each vertex for current LOD
		for (std::uint32_t i = 0; i < numOfFaces; ++i) {
			std::array<std::uint32_t, 3> faces;
			std::memcpy(faces.data(), buffer.data() + position, sizeof(std::uint32_t) * 3);
			position += (sizeof(std::uint32_t) * 3);
			lodInfo.faces.push_back(faces);
		}
		allLodInfo.push_back(lodInfo);
	}

	mesh->setLodInfo(allLodInfo);
	if (isSkinned) parseSkinnedMesh(buffer, position, numOfVerticesPerLOD);

	// Find correct material and add it to mesh
	for (const auto& currentMaterial : m_materials) {
		if (materialName == currentMaterial->getName()) {
			mesh->setMaterial(currentMaterial);
			break;
		}
	}
}


	
void OvoParser::parseBones(const std::vector<char>& buffer, std::size_t& position) {
	// Light name 
	std::size_t boneNameLen = std::strlen(buffer.data() + position);
	//std::string boneName{ buffer.data() + position, buffer.data() + position + boneNameLen };
	position += boneNameLen + 1;

	// Light Matrix
	//glm::mat4 boneMatrix;
	//std::memcpy(&boneMatrix, buffer.data() + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

	// Number of children nodes
	//std::uint32_t numOfChildren;
	//std::memcpy(&numOfChildren, buffer.data() + position, sizeof(std::uint32_t));
	position += sizeof(std::uint32_t);

	// Optional target name
	std::size_t targetLength = std::strlen(buffer.data() + position);
	//std::string targetName{ buffer.data() + position, buffer.data() + position + targetLength };
	position += targetLength + 1;

	// box min corner
	//glm::vec3 bBoxMin;
	//memcpy(&bBoxMin, buffer.data() + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// box max corner
	//glm::vec3 bBoxMax;
	//memcpy(&bBoxMax, buffer.data() + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);
}


void OvoParser::parseSkinnedMesh(const std::vector<char>& buffer, std::size_t& position, const std::vector<std::uint32_t>& numOfVerticesPerLOD) {
	// Pose matrix 
	glm::mat4 poseMatrix;
	std::memcpy(&poseMatrix, buffer.data() + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

	// Bone list
	std::uint32_t numOfBones;
	std::memcpy(&numOfBones, buffer.data() + position, sizeof(std::uint32_t));
	position += sizeof(std::uint32_t);

	for (std::uint32_t i = 0; i < numOfBones; ++i) {
		// Name of bone -- Ignored
		std::size_t boneNaneLen = std::strlen(buffer.data() + position);
		//std::string boneName{ buffer.data() + position, buffer.data() + position + boneNaneLen };
		position += boneNaneLen + 1;

		// Inverted BoneMatrix -- Ignored
		//glm::mat4 boneMatrix;
		//std::memcpy(&boneMatrix, buffer.data() + position, sizeof(glm::mat4));
		position += sizeof(glm::mat4);
	}

	for (std::size_t i = 0; i < numOfVerticesPerLOD.size(); ++i) {
		// Bone weight per vertex -- Ignored
		for (std::uint32_t inner_i = 0; i < numOfVerticesPerLOD[i]; ++inner_i) {
			//std::array<std::uint32_t, 4> boneIndexes;
			//std::memcpy(boneIndexes.data(), buffer.data() + position, sizeof(std::uint32_t) * 4);
			position += (sizeof(std::uint32_t) * 4);

			// Bone weights -- Ignored
			//std::array<std::uint16_t, 4> boneWeights;
			//std::memcpy(boneWeights.data(), buffer.data() + position, sizeof(std::uint16_t) * 4);
			//glm::vec4 boneWeight;
			//boneWeight.x = glm::unpackHalf1x16(boneWeights[0]);
			//boneWeight.y = glm::unpackHalf1x16(boneWeights[1]);
			//boneWeight.z = glm::unpackHalf1x16(boneWeights[2]);
			//boneWeight.w = glm::unpackHalf1x16(boneWeights[3]);
			position += (sizeof(std::uint16_t) * 4);
		}
	}
}

void OvoParser::parsePhysicsProperties(const std::vector<char>& buffer, std::size_t& position) {
	struct PhysProps {
		unsigned char type;
		unsigned char contCollisionDetection;
		unsigned char collideWithRBodies;
		unsigned char hullType;
		glm::vec3 massCenter;
		float mass;
		float staticFriction;
		float dynamicFriction;
		float bounciness;
		float linearDamping;
		float angularDamping;
		unsigned int nrOfHulls;
		unsigned int _pad;
		void* physObj;
		void* hull;
	};

	PhysProps mp;
	memcpy(&mp, buffer.data() + position, sizeof(PhysProps));
	position += sizeof(PhysProps);

	// Custom hull(s) used?
	if (mp.nrOfHulls) {
		for (unsigned int c = 0; c < mp.nrOfHulls; c++) {
			unsigned int nrOfVertices;
			memcpy(&nrOfVertices, buffer.data() + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			unsigned int nrOfFaces;
			memcpy(&nrOfFaces, buffer.data() + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			// Hull centroid:
			position += sizeof(glm::vec3);

			// Vertex coordinates
			for (unsigned int c = 0; c < nrOfVertices; c++) {
				position += sizeof(glm::vec3);
			}
			// Faces coordinates
			for (unsigned int c = 0; c < nrOfFaces; c++) {
				position += sizeof(unsigned int) * 3;
			}
		}
	}
}
