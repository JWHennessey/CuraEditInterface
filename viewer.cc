#include "Scene.hh"
#include <QtGui>
#include <QGLWidget>


using namespace Qt;

#warning "viewer.cc included"


class GraphicsView : public QGraphicsView
{
public:
    GraphicsView()
    {
        setWindowTitle(tr("Cura Edit Interface"));
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    GraphicsView view;
    view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    Scene *scene = new Scene();
    view.setScene(scene);
    view.show();

    std::cout << "main" << "\n";

    view.resize(1024, 768);

    return app.exec();
}

