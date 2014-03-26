#ifndef SCENET_HH
#define SCENET_HH

//#warning "Include Scene.hh"

#include <QGraphicsScene>
#include <QLabel>
#include <QTime>
#include <QtOpenGL>
//#include "ConsoleReader.hh"
#include "zmq.hpp"
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif
#include <OpenMesh/Core/IO/MeshIO.hh>
#include "QtModelT.hh"
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/Utils/GenProg.hh>
#include <OpenMesh/Core/Utils/color_cast.hh>
#include <OpenMesh/Core/Mesh/Attributes.hh>
#include <string>

#warning "SceneT.hh included"

using namespace Qt;

template <typename M>
class SceneT : public QGraphicsScene
{

public:
    /// default constructor
    typedef M MyMesh;
    SceneT();
    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);

public slots:
    //void updateText();
    void startZMQThread();

private:
    float m_distance;
    float m_vertical;
    float m_horizontal;
    float radius;
    QVector3D m_rotation;
    const float TANSLATE_SPEED;
    OpenMesh::IO::Options _options;
    MyMesh mesh;
    QtModelT<M>* model;
    void loadModel(std::string filename);
    QColor m_backgroundColor;
    QGraphicsTextItem *cinTextItem;
    QString cinText;
    static void zmqThread();
    bool firstDraw;
    bool hasModel;
    void setDefaultMaterial();
    void setDefaultLight();
    //zmq::context_t context;
    //zmq::socket_t *socket;

    //ConsoleReader cr;
};

#if !defined(SCENET_CC)
#define SCENET_CC_Templates
#  include "SceneT.cc"
#endif

#endif

