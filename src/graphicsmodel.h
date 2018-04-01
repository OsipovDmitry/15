#ifndef GRAPHICSMODEL_H
#define GRAPHICSMODEL_H

#include <memory>

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace graphics {

class Scene;
using ScenePtr = std::shared_ptr<Scene>;

class Material;
using MaterialPtr = std::shared_ptr<Material>;

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;

class Model {
public:
    ~Model();

    glm::vec3 position() const;
    glm::vec3 angles() const;
    glm::vec3 scale() const;
    glm::mat4x4 transformMatrix() const;

    void setPosition(const glm::vec3& val);
    void setAngles(const glm::vec3& val);
    void setScale(const glm::vec3& val);

private:
    Model(ScenePtr pScene, MaterialPtr pMaterial, MeshPtr pMesh);

    ScenePtr m_pScene;
    MaterialPtr m_pMaterial;
    MeshPtr m_pMesh;

    glm::vec3 m_position, m_angles, m_scale;

    friend class Scene;
};

}

#endif // GRAPHICSMODEL_H
