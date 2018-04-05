#ifndef GRAPHICSMESH_H
#define GRAPHICSMESH_H

#include <vector>
#include <memory>

#include <QGL>

namespace graphics {

class Controller;
using ControllerPtr = std::shared_ptr<Controller>;

class Mesh {
public:
    ~Mesh();

private:
    Mesh(ControllerPtr pController, const std::vector<float>& vertices, const std::vector<uint32_t> indices);

    ControllerPtr m_pController;
	GLuint m_vertexArray, m_vertexBuffer, m_indexBuffer;
    uint32_t m_numIndices;

    friend class Controller;
	friend class SceneLayer;
};

}

#endif // GRAPHICSMESH_H
