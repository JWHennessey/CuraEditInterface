#ifndef MODEL_HH
#define MODEL_HH

#include <iostream>
#include <fstream>
#include <QString>
#include <QVector>
#include <QPainter>
#include <QGraphicsItem>
#include "Scene.hh"
#include "MyMesh.hh"
#include <QVector3D>
#include <eigen3/Eigen/Dense>
#include <nanoflann.hpp>

//#include <flann/io/hdf5.h>

//#warning "QtModelT.hh included"

using namespace Qt;
using namespace OpenMesh;
using namespace Eigen;

template <typename M>
class QtModelT : public QGraphicsItem
{
public:
    typedef M MyMesh;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
public:
     M mesh;
    QtModelT(M& m);
    ~QtModelT();
    void render();


private:
    QVector3D modelRotation;
    QColor modelColor;
    GLfloat vertical;
    GLfloat horizontal;
    GLfloat depth;
    const float deg2Rad;
    void calcNormals();

};

#if defined(OM_INCLUDE_TEMPLATES) && !defined(MODEL_CC)
#  define SCENE_TEMPLATES
#  include "QtModelT.cc"
#endif

#endif
