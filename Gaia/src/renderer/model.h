#pragma once
#include <resources/resource.h>
#include <renderer/mesh.h>

struct aiNode;
struct aiMesh;
struct aiScene;

namespace Gaia {
	struct BoneData
	{
		mat4 m_offest;
		std::string m_name;
	};

	struct MeshNode
	{
		MeshNode(MeshNode* p) :m_parent(p) {}
		~MeshNode();
		MeshNode* find(const std::string& name);

		MeshNode* m_parent;
		std::vector<MeshNode*> m_children;
		std::vector<BoneData*> m_bones;
		std::string m_name;
		mat4 m_transform;
	};

	class Model : public Resource{
	public:
		Model(const std::string& path, const e_Extension ext)
			: Resource(path, ext) {}
		Extensions(e_Extension::obj);

		void draw()const;
		bool load_internal()override;
		bool unload_internal()override;

	private:
		void assimp_load();
		void process_node(aiNode* ai_node, MeshNode* parent, const aiScene* scn);
		void process_mesh(aiMesh* ai_mesh, const aiScene* scn);

		std::vector<shared<Mesh>> m_meshes;
		MeshNode* m_hierarchy;
		std::vector<BoneData*> m_bones;
		std::map<std::string, int> m_bone_mapping;
	};
}