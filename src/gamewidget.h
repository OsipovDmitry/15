#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <memory>

#include <QOpenGLWidget>

class QTimer;

namespace graphics {

class Controller;
using ControllerPtr = std::shared_ptr<Controller>;

}

namespace game {

class AbstractGame;
using AbstractGamePtr = std::shared_ptr<AbstractGame>;
using AbstractGameWPtr = std::weak_ptr<AbstractGame>;

class GameWidget : public QOpenGLWidget {
public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

    graphics::ControllerPtr graphicsController() const;

    void setGame(AbstractGamePtr pGame);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void wheelEvent(QWheelEvent* pEvent) override;

private:
    QTimer *m_pTimer;
    graphics::ControllerPtr m_pRenderer;
    AbstractGameWPtr m_pGame;
    qint64 m_startTime;
    uint64_t m_lastUpdateTime;
    int32_t m_mouseX, m_mouseY;

};

}

#endif // GAMEWIDGET_H
