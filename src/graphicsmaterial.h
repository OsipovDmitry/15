#ifndef GRAPHICSMATERIAL_H
#define GRAPHICSMATERIAL_H

#include <string>
#include <memory>

#include <QGL>

class QImage;

namespace graphics {

class Controller;
using ControllerPtr = std::shared_ptr<Controller>;

class Material
{
public:
    ~Material();

private:
    Material(ControllerPtr pController, const std::string& filename);
    Material(ControllerPtr pController, const QImage& image);

    void load(const QImage& image);

    ControllerPtr m_pController;
    GLuint m_id;

    friend class Controller;
	friend class SceneLayer;
};

}

#endif // GRAPHICSMATERIAL_H
