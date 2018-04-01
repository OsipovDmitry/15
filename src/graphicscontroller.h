#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <memory>
#include <vector>
#include <string>

class QGLContext;
class QImage;

namespace game {
class GameWidget;
}

namespace graphics {

class Scene;
using ScenePtr = std::shared_ptr<Scene>;
using SceneWPtr = std::weak_ptr<Scene>;

class Material;
using MaterialPtr = std::shared_ptr<Material>;

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;

class Controller : public std::enable_shared_from_this<Controller>
{
public:
	Controller(QGLContext *pGLContext);
	~Controller();

	QGLContext *context() const;
	const int32_t* viewport() const;

	ScenePtr createScene();
	MaterialPtr createMaterial(const std::string& filename);
	MaterialPtr createMaterial(const QImage& image);
	MeshPtr createMesh(const std::vector<float>& vertices, const std::vector<uint32_t> indices);

	void setCurrentScene(ScenePtr pScene);

private:
	QGLContext *m_pGLContext;
	SceneWPtr m_pCurrentScene;
	int32_t m_viewport[4];

	void render();
	void resize(int32_t width, int32_t height);

	friend class game::GameWidget;
};

}

#endif // GRAPHICSCONTROLLER_H
