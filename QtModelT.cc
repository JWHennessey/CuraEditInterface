#ifndef MODEL_CC
#define MODEL_CC


#include "QtModelT.hh"
#include <math.h> 
#include <QFile>
#include <QTextStream>
#include <QVarLengthArray>
#include <QtOpenGL>
#include <random>
#include <cmath>
#include <math.h> 

//#warning "QtModelT.cc incuded"

template <typename M>
QtModelT<M>::QtModelT(M& m)
  : modelColor(100, 100, 100)
  , vertical(0.0f)
  , horizontal(0.0f)
  , depth(0.0f)
  , deg2Rad(0.0174532925)
{
  mesh = m;

  double min_x, max_x, min_y, max_y, min_z, max_z;
  bool first = true;
  for (typename M::VertexIter v_it=mesh.vertices_begin(); v_it!=mesh.vertices_end(); ++v_it) 
  {
    if(first){
      min_x = mesh.point(*v_it)[0];
      max_x = mesh.point(*v_it)[0];
      min_y = mesh.point(*v_it)[1];
      max_y = mesh.point(*v_it)[1];
      min_z = mesh.point(*v_it)[2];
      max_z = mesh.point(*v_it)[2];
      first = false;
    }

    if(mesh.point(*v_it)[0] < min_x )
      min_x = mesh.point(*v_it)[0];
    else if(mesh.point(*v_it)[0] > max_x )
      max_x = mesh.point(*v_it)[0];

    if(mesh.point(*v_it)[1] < min_y )
      min_y = mesh.point(*v_it)[1];
    else if(mesh.point(*v_it)[1] > max_y )
      max_y = mesh.point(*v_it)[1];

    if(mesh.point(*v_it)[2] < min_z )
      min_z = mesh.point(*v_it)[2];
    else if(mesh.point(*v_it)[2] > max_z )
      max_z = mesh.point(*v_it)[2];

  }
  typedef typename M::Point Point;
  for (typename M::VertexIter v_it=mesh.vertices_begin(); v_it!=mesh.vertices_end(); ++v_it) 
  {
    mesh.set_point( *v_it, Point(
          2.0*(mesh.point(*v_it)[0]-min_x)/(max_x-min_x) - 1.0,
          2.0*(mesh.point(*v_it)[1]-min_y)/(max_y-min_y) - 1.0,
          2.0*(mesh.point(*v_it)[2]-min_z)/(max_z-min_z) - 1.0)
    );
  }

  calcNormals();
}


template <typename M>
QtModelT<M>::~QtModelT()
{

}

template <typename M>
void
QtModelT<M>::render()
{
    typename M::ConstFaceIter    fIt(mesh.faces_begin()),
                                 fEnd(mesh.faces_end());

    typename M::ConstFaceVertexIter fvIt;

    //std::cout << "Render" << "\n";
    glPushMatrix();
    glTranslatef(horizontal, vertical, 0);
    glRotatef(modelRotation.x(), 1, 0, 0);
    glRotatef(modelRotation.y(), 0, 1, 0);
    glRotatef(modelRotation.z(), 0, 0, 1);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);

    unsigned int index = 0;
    for (; fIt!=fEnd; ++fIt)
    {
        glLoadName(index);
        glBegin(GL_TRIANGLES);
        glNormal3fv( &mesh.normal(*fIt)[0] );
        fvIt = mesh.cfv_iter(*fIt);
        glVertex3fv( &mesh.point(*fvIt)[0] );
        ++fvIt;
        glVertex3fv( &mesh.point(*fvIt)[0] );
        ++fvIt;
        glVertex3fv( &mesh.point(*fvIt)[0] );
        glEnd();
        index++;
     }

    //glBegin(GL_LINES);
    //glLineWidth(2.0f);
    //for (typename M::VertexIter v_it=mesh.vertices_begin(); v_it!=mesh.vertices_end(); ++v_it) 
    //{
      //glColor3b (255, 255, 255);
      //glVertex3f(mesh.point(*v_it)[0], mesh.point(*v_it)[1], mesh.point(*v_it)[2]);
      //glVertex3f(mesh.point(*v_it)[0]+mesh.normal(*v_it)[0], mesh.point(*v_it)[1]+mesh.normal(*v_it)[1], mesh.point(*v_it)[2]+mesh.normal(*v_it)[2]);

    //}
    //glEnd();

    glPopMatrix();

}

template <typename M>
void
QtModelT<M>::select(int faceNumber){
  typename M::FaceHandle face = mesh.face_handle(faceNumber);
  mesh.set_color(face, typename M::Color(255,255,255));
}



template <typename M>
void
QtModelT<M>::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  std::cout << "paint" << "\n";
  painter->drawRect(boundingRect());
  painter->beginNativePainting();
  glPushMatrix();
  glTranslatef(horizontal, vertical, 0);
  glRotatef(modelRotation.x(), 1, 0, 0);
  glRotatef(modelRotation.y(), 0, 1, 0);
  glRotatef(modelRotation.z(), 0, 0, 1);

  glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);

  if ( mesh.has_vertex_colors() )
  {
    glEnableClientState( GL_COLOR_ARRAY );
    glColorPointer(3, GL_FLOAT, 0, mesh.vertex_colors());
  }
  //glColor4f(modelColor.redF(), modelColor.greenF(), modelColor.blueF(), 1.0f);
  glVertexPointer(3, GL_FLOAT, 0, mesh.points());
  glDrawArrays( GL_POINTS, 0, static_cast<GLsizei>(mesh.n_vertices()) );

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_DEPTH_TEST);

  glDisableClientState(GL_COLOR_ARRAY);  

  glPopMatrix();

  painter->endNativePainting();

}


template <typename M>
QRectF 
QtModelT<M>::boundingRect() const
{
  return QRectF(0,0, 1024, 768);
}


#endif
