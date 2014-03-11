#ifndef SCENE_CC
#define SCENE_CC

//#warning "Include Scene.cc"

#include <thread>
#include "Scene.hh"
#include <QVector3D>
#include "GLUT/glut.h"
#include <QtGui>
#include <QtOpenGL>
//#warning "Scene.cc included"
#include "zmq.hpp"
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif

Scene::Scene()
{
   cinTextItem = new QGraphicsTextItem;
   cinTextItem->setPos(150,70); 
   cinTextItem->setDefaultTextColor(QColor(255, 255, 255));
   addItem(cinTextItem);
   cinText = QString("Holding Text");

   std::thread t1(zmqThread);

   std::cout << "Hello World from c++" << "\n";
}

void
Scene::zmqThread()
{
  std::cout << "Hello World" << "\n";
 //  Prepare our context and socket
    //zmq::context_t context (1);
    //zmq::socket_t socket (context, ZMQ_REP);
    //socket.bind ("tcp://*:5555");

    //while (true) {
        //zmq::message_t request;

        ////  Wait for next request from client
        //socket.recv (&request);
        //std::cout << "Received Hello" << std::endl;

        ////  Do some 'work'
//#ifndef _WIN32
        //sleep(1);
//#else
    //Sleep (1);
//#endif

        ////  Send reply back to client
        //zmq::message_t reply (5);
        //memcpy ((void *) reply.data (), "World", 5);
        //socket.send (reply);
    //}
}


void Scene::drawForeground(QPainter *painter, const QRectF &rect)
{
  cinTextItem->setPlainText(cinText);
}


void Scene::drawBackground(QPainter *painter, const QRectF &rect)
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

//void Scene::updateText()
//{
//  std::cout << "Update Text Called" << "\n";
//  cinText = cr.getText();
//}

#endif
