#ifndef SCENET_CC
#define SCENET_CC

//#warning "Include Scene.cc"

#include <thread>
#include "SceneT.hh"
#include <QVector3D>
#include "GLUT/glut.h"
#include <QtGui>
#include <QtOpenGL>

#include "zmq.hpp"
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif

#warning "SceneT.cc included YYYYYYYY xxxxxx"

template <typename M>
SceneT<M>::SceneT()
{
   cinTextItem = new QGraphicsTextItem;
   cinTextItem->setPos(150,70); 
   cinTextItem->setDefaultTextColor(QColor(255, 255, 255));
   addItem(cinTextItem);
   cinText = QString("Holding Text");

   std::cout << "Hello World from c++" << "\n";
   firstDraw = true;
   hasModel = false;
   //startZMQThread();
}


template <typename M>
void SceneT<M>::startZMQThread()
{
  std::thread t1(zmqThread);
  t1.join();
}

template <typename M>
void
SceneT<M>::zmqThread()
{

  //while(true){
    //std::cout << "Hello World" << "\n";
  //}
    //Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
      zmq::message_t request;

      //  Wait for next request from client
      socket.recv (&request);
      std::cout << "Received Hello" << std::endl;

        //  Do some 'work'
#ifndef _WIN32
        sleep(1);
#else
    Sleep (1);
#endif

      //  Send reply back to client
      zmq::message_t reply (5);
      memcpy ((void *) reply.data (), "World", 5);
      socket.send (reply);
    }
}


template <typename M>
void
SceneT<M>::setDefaultMaterial(void)
{
  GLfloat mat_a[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat mat_d[] = {0.7, 0.7, 0.5, 1.0};
  GLfloat mat_s[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat shine[] = {120.0};
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_a);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_d);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_s);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}


//----------------------------------------------------------------------------

template <typename M>
void
SceneT<M>::setDefaultLight(void)
{
  GLfloat pos1[] = { 0.1,  0.1, -0.02, 0.0};
  GLfloat pos2[] = {-0.1,  0.1, -0.02, 0.0};
  GLfloat pos3[] = { 0.0,  0.0,  0.1,  0.0};
  GLfloat col1[] = { 0.7,  0.7,  0.8,  1.0};
  GLfloat col2[] = { 0.8,  0.7,  0.7,  1.0};
  GLfloat col3[] = { 1.0,  1.0,  1.0,  1.0};
 
  glEnable(GL_LIGHT0);    
  glLightfv(GL_LIGHT0,GL_POSITION, pos1);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,  col1);
  glLightfv(GL_LIGHT0,GL_SPECULAR, col1);
  
  glEnable(GL_LIGHT1);  
  glLightfv(GL_LIGHT1,GL_POSITION, pos2);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,  col2);
  glLightfv(GL_LIGHT1,GL_SPECULAR, col2);
  
  glEnable(GL_LIGHT2);  
  glLightfv(GL_LIGHT2,GL_POSITION, pos3);
  glLightfv(GL_LIGHT2,GL_DIFFUSE,  col3);
  glLightfv(GL_LIGHT2,GL_SPECULAR, col3);
}

template <typename M>
void
SceneT<M>::drawForeground(QPainter *painter, const QRectF &rect)
{
  cinTextItem->setPlainText(cinText);
  if(firstDraw)
  {
    firstDraw = false;
  }
  else if(hasModel)
  {
    std::cout << "Has Model Update" << std::endl;
    painter->beginNativePainting();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    gluPerspective(70, width() / height(), 0.01, 1000);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    setDefaultMaterial();

    setDefaultLight();  
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);
    //glutSolidTeapot(0.5);

    glTranslatef(m_horizontal, m_vertical, -m_distance);
    glRotatef(m_rotation.x(), 1, 0, 0);
    glRotatef(m_rotation.y(), 0, 1, 0);
    glRotatef(m_rotation.z(), 0, 0, 1);

    glEnable(GL_MULTISAMPLE);
    
    std::cout << "Render Outside" << std::endl;
    mesh.render();

    glDisable(GL_MULTISAMPLE);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();


    painter->endNativePainting();
  }else{
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");
    zmq::message_t request;
    //  Wait for next request from client
    std::cout << "Waiting for request" << std::endl;
    socket.recv (&request);
    std::cout << "Received request" << std::endl;
    std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
    std::cout << rpl.substr(0, 1) << std::endl;
    if(rpl.substr(0,1)=="0")
    {
      std::cout << rpl << std::endl;
      std::cout << "New Model" << std::endl;
      loadModel(rpl);
      hasModel = true;
    }
  }
}


template <typename M>
void 
SceneT<M>::drawBackground(QPainter *painter, const QRectF &rect)
{
  if (painter->paintEngine()->type() != QPaintEngine::OpenGL
      && painter->paintEngine()->type() != QPaintEngine::OpenGL2)
  {
    qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
    return;
  }
  
  painter->beginNativePainting();
  glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), 1.0f);
  //glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  painter->endNativePainting();

}

template <typename M>
void
SceneT<M>::loadModel(String filename)
{
  if(OpenMesh::IO::read_mesh(mesh, filename.erase(0,1), _options))
  {
    //
    std::cout << "Mesh Loaded" << "\n";
  }
}


//void Scene::updateText()
//{
//  std::cout << "Update Text Called" << "\n";
//  cinText = cr.getText();
//}

#endif
