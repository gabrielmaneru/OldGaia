#include "gaia_pch.h"
#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Gaia {
	inline mat4 mat4toglm(const aiMatrix4x4& m)
	{
		return glm::transpose(glm::make_mat4x4(&m.a1));
	}

	MeshNode::~MeshNode()
	{
	}
	MeshNode * MeshNode::find(const std::string & name)
	{
		if (m_name == name)
			return this;

		for (auto c : m_children)
		{
			MeshNode* res = c->find(name);
			if (res != nullptr)
				return res;
		}
		return nullptr;
	}

	void Model::draw() const
	{
		for (auto& m : m_meshes)
			m->draw();
	}

	bool Model::load_internal()
	{
		assimp_load();
		return false;
	}
	bool Model::unload_internal()
	{
		return false;
	}
	void Model::assimp_load()
	{
		Assimp::Importer imp{};
		u32 mesh_flags = aiProcessPreset_TargetRealtime_MaxQuality;
		const aiScene* scn = imp.ReadFile(m_path, mesh_flags);
		GAIA_EASSERT(scn, "Mesh not found at {0}", m_path);
		//GAIA_EASSERT(scn->mFlags & AI_SCENE_FLAGS_INCOMPLETE, "Incomplete mesh {0}", m_path);
		GAIA_EASSERT(scn->HasMeshes(), "None meshes found at {0}", m_path);

		m_hierarchy = new MeshNode(nullptr);
		process_node(scn->mRootNode, m_hierarchy, scn);

	}
	void Model::process_node(aiNode * ai_node, MeshNode * parent, const aiScene * scn)
	{
		parent->m_name = { ai_node->mName.data };
		parent->m_transform = mat4toglm(ai_node->mTransformation);

		// Add Meshes
		for (u32 i = 0; i < ai_node->mNumMeshes; ++i) {
			aiMesh* mesh = scn->mMeshes[ai_node->mMeshes[i]];
			process_mesh(mesh, scn);
		}

		// Continue the hierarchy
		for (u32 i = 0; i < ai_node->mNumChildren; ++i) {
			MeshNode* pC = new MeshNode(parent);
			parent->m_children.push_back(pC);
			process_node(ai_node->mChildren[i], pC, scn);
		}
	}
	void Model::process_mesh(aiMesh * ai_mesh, const aiScene * scn)
	{
		// Get counters
		u32 vtx_count = ai_mesh->mNumVertices;
		u32 tri_count = ai_mesh->mNumFaces;

		// Create a new mesh
		m_meshes.emplace_back(new_shared<Mesh>(vtx_count));
		auto mesh = m_meshes.back();
		// Ger vertex buffer
		VertexBuf& vb = mesh->m_vb;

		// Allocate indices buffer
		vb.m_indices.resize(tri_count * 3, 0u);
		// Copy indices for each face
		for (u32 i = 0; i < tri_count; i++)
			std::memcpy(&vb.m_indices[i*3], ai_mesh->mFaces[i].mIndices, 3*sizeof(u32));

		// Copy vertex positions
		std::memcpy(vb.m_position.data(), ai_mesh->mVertices, vtx_count * sizeof(vec3));

		// Copy vertex normals
		if(ai_mesh->HasNormals())
			std::memcpy(vb.m_normal.data(), ai_mesh->mNormals, vtx_count * sizeof(vec3));

		// Copy vertex texture coordinates
		if (ai_mesh->HasTextureCoords(0))
			for(u32 v =0; v < vtx_count; ++v)
				std::memcpy(&vb.m_uv_coord[v], &ai_mesh->mTextureCoords[0][v], sizeof(vec2));

		// Copy vertex tangents & bitangents
		if(ai_mesh->HasTangentsAndBitangents())
			std::memcpy(vb.m_tangent.data(), ai_mesh->mTangents, vtx_count * sizeof(vec3)),
			std::memcpy(vb.m_bitangent.data(), ai_mesh->mBitangents, vtx_count * sizeof(vec3));

		// Process bone information
		for (u32 i = 0; i < ai_mesh->mNumBones; ++i) {
			const aiBone* bone = ai_mesh->mBones[i];
			std::string name = bone->mName.data;

			int bone_id;
			auto it = m_bone_mapping.find(name);
			if (it == m_bone_mapping.end())
			{
				bone_id = (int)m_bones.size();
				m_bone_mapping[name] = bone_id;

				m_bones.push_back(new BoneData());
				m_bones.back()->m_offest = mat4toglm(bone->mOffsetMatrix);
				m_bones.back()->m_name = name;
			}
			else
				bone_id = it->second;

			for (u32 w = 0; w < bone->mNumWeights; ++w) {
				const aiVertexWeight& weight = bone->mWeights[w];
				for (u8 j = 0; j < 4; ++j) {
					if (vb.m_weights[weight.mVertexId][j] == 0.0f) {
						vb.m_weights[weight.mVertexId][j] = weight.mWeight;
						vb.m_boneid [weight.mVertexId][j] = bone_id;
						break;
					}
				}
			}
		}
		mesh->load();

		//TODO Material

	}
}
