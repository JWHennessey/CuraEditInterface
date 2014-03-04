#ifndef SCENE_HH
#define SCENE_HH

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
//#warning "Scene.hh included"

using namespace Qt;

class Scene : public QGraphicsScene
{
  Q_OBJECT
public:
    /// default constructor
    Scene();
    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);

public slots:
    //void updateText();

private:
    QColor m_backgroundColor;
    QGraphicsTextItem *cinTextItem;
    QString cinText;
    zmq::context_t context;
    zmq::socket_t *socket;

    //ConsoleReader cr;
};

#if !defined(SCENE_CC)
#define SCENE_CC
#  include "Scene.cc"
#endif

#endif

