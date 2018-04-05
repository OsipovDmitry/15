#ifndef GARPHICSSCENE_H
#define GARPHICSSCENE_H

#include <array>
#include <memory>

#include "glm/mat4x4.hpp"

class QGLContext;

namespace graphics {

class Controller;
using ControllerPtr = std::shared_ptr<Controller>;

class SceneLayer;
using SceneLayerPtr = std::shared_ptr<SceneLayer>;

enum class SceneLayerId : uint8_t {
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
	SceneLayerPtr layer(SceneLayerId id);
	void setViewMatrix(const glm::mat4x4& value);

private:
	Scene(ControllerPtr pController);
	void render() const;

	glm::mat4x4 projMatrix(SceneLayerId layer) const;
	bool depthTestState(SceneLayerId layer) const;

	ControllerPtr m_pController;
	std::array<SceneLayerPtr, static_cast<size_t>(SceneLayerId::Count)> m_layers;

	friend class Controller;
};

}

#endif // GARPHICSSCENE_H
