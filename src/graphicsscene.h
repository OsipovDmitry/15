#ifndef GARPHICSSCENE_H
#define GARPHICSSCENE_H

#include <array>
#include <list>
#include <memory>

#include "glm/mat4x4.hpp"

class QGLContext;

namespace graphics {

class Controller;
using ControllerPtr = std::shared_ptr<Controller>;

class Material;
using MaterialPtr = std::shared_ptr<Material>;

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;

class Model;
using ModelPtr = std::shared_ptr<Model>;

enum class SceneLayer : uint8_t {
	Background,
	Objects,
	GUI,
	Count,
};

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	~Scene();

	void clear();
	ModelPtr addModel(SceneLayer layer, MaterialPtr pMaterial, MeshPtr pMesh);

	void setViewMatrix(const glm::mat4x4& value);

	ModelPtr selectObject(SceneLayer layer, int32_t x, int32_t y);

private:
	Scene(ControllerPtr pController);
	void render() const;
	void renderBackground(const std::list<ModelPtr>& listModels) const;
	void renderObjects(const std::list<ModelPtr>& listModels) const;
	void renderGUI(const std::list<ModelPtr>& listModels) const;
	void renderModel(ModelPtr pModel) const;

	glm::mat4x4 viewMatrix(SceneLayer layer) const;
	glm::mat4x4 projMatrix(SceneLayer layer) const;

	ControllerPtr m_pController;
	std::array<std::list<ModelPtr>, static_cast<size_t>(SceneLayer::Count)> m_objects;
	glm::mat4x4 m_viewMatrix;

	friend class Controller;
};

}

#endif // GARPHICSSCENE_H
