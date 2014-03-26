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

#include <OpenMesh/Core/IO/MeshIO.hh>
#include "SceneT.hh"
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include "MyMesh.hh"
//#warning "Scene.hh included"

#warning "Scene.hh included xxxxxx"


using namespace Qt;

class Scene : public SceneT<MyMesh>
{
  Q_OBJECT
public:
    /// default constructor
    Scene() : SceneT<MyMesh>()
    {
      std::cout << "Scene" << "\n";
    }
};

//#if !defined(SCENE_CC)
//#define SCENE_CC
//#  include "Scene.cc"
//#endif

#endif

