//#include <QApplication>
//#include <QWidget>
//#include <QPainter>
//#include <QTimer>
//
//#include <iostream>
//
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//class Vector2D
//{
//public:
//   Vector2D();
//   Vector2D(double x, double y);
//   ~Vector2D() {}
//
//   double x() const;
//   void x(double value);
//
//   double y() const;
//   void y(double value);
//
//   double magnitude();
//   Vector2D normalise();
//
//private:
//   double m_x, m_y;
//};
//
//Vector2D::Vector2D() : m_x(0.0), m_y(0.0)
//{
//}
//
//Vector2D::Vector2D(double x, double y) : m_x(x), m_y(y)
//{
//}
//
//double Vector2D::x() const
//{
//   return m_x;
//}
//
//void Vector2D::x(double value)
//{
//   m_x = value;
//}
//
//double Vector2D::y() const
//{
//   return m_y;
//}
//
//void Vector2D::y(double value)
//{
//   m_y = value;
//}
//
//double Vector2D::magnitude()
//{
//   return sqrt(m_x*m_x + m_y*m_y);
//}
//
//Vector2D Vector2D::normalise()
//{
//   double mag = magnitude();
//   //std::cout << "Mag = " << mag << std::endl;
//   //std::cout << "x = " << m_x << std::endl;
//   //std::cout << "y = " << m_y << std::endl;
//   //std::cout << "x_n = " << m_x/mag << std::endl;
//   //std::cout << "y_n = " << m_y/mag << std::endl;
//   return Vector2D(m_x / mag, m_y / mag);
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//
//typedef int BodyIdT;
//
//class Body
//{
//public:
//   Body(BodyIdT id);
//   Body(BodyIdT id, double radius);
//   Body(BodyIdT id, double radius, Vector2D position);
//   ~Body();
//
//   Vector2D position() const;
//   void position(Vector2D position);
//
//   Vector2D velocity() const;
//   void velocity(Vector2D velocity);
//
//   BodyIdT id() const;
//
//   double radius() const;
//   void radius(double radius);
//
//   bool isStatic() const;
//   void isStatic(bool isStatic);
//
//private:
//   const BodyIdT m_id;
//   double m_radius;
//   bool m_isStatic;
//   Vector2D m_position;
//   Vector2D m_velocity;
//};
//
//Body::Body(BodyIdT id) : m_id(id), m_isStatic(false)
//{
//}
//
//Body::Body(BodyIdT id, double radius) : m_id(id), m_radius(radius), m_isStatic(false)
//{
//}
//
//Body::Body(BodyIdT id, double radius, Vector2D position) : m_id(id), m_radius(radius), m_position(position), m_isStatic(false)
//{
//}
//
//Body::~Body()
//{
//
//}
//
//Vector2D Body::position() const
//{
//   return m_position;
//}
//
//void Body::position(Vector2D position)
//{
//   m_position = position;
//}
//
//Vector2D Body::velocity() const
//{
//   return m_velocity;
//}
//
//void Body::velocity(Vector2D velocity)
//{
//   m_velocity = velocity;
//}
//
//BodyIdT Body::id() const
//{
//   return m_id;
//}
//
//double Body::radius() const
//{
//   return m_radius;
//}
//
//void Body::radius(double radius)
//{
//   m_radius = radius;
//}
//
//bool Body::isStatic() const
//{
//   return m_isStatic;
//}
//
//void Body::isStatic(bool isStatic)
//{
//   m_isStatic = isStatic;
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//class BodySimulation
//{
//public:
//   BodySimulation();
//   ~BodySimulation();
//
//   void addBody(double radius, Vector2D position, Vector2D velocity, bool staticBody = false);
//   std::vector<Body> bodies() const;
//
//   void advance();
//
//private:
//   int m_nextBodyId = 0;
//   std::vector<Body> m_bodies;
//};
//
//BodySimulation::BodySimulation()
//{
//
//}
//
//BodySimulation::~BodySimulation()
//{
//
//}
//
//void BodySimulation::addBody(double radius, Vector2D position, Vector2D velocity, bool staticBody)
//{
//   Body body(m_nextBodyId++, radius, position);
//   body.velocity(velocity);
//   body.isStatic(staticBody);
//   m_bodies.push_back(body);
//}
//
//std::vector<Body> BodySimulation::bodies() const
//{
//   return m_bodies;
//}
//
//void BodySimulation::advance()
//{
//   // Loop bodies and advance in time
//   for (auto body : m_bodies)
//   {
//      if (!body.isStatic())
//      {
//         std::cout << "Calculating position for body at position = (" << body.position().x() << ", " << body.position().y() << ")" << std::endl;
//         std::cout << "Calculating force on body " << body.id() << std::endl;
//         for (auto forceFromBody : m_bodies)
//         {
//            if (forceFromBody.id() != body.id())
//            {
//               std::cout << "\tCalculating force from body " << forceFromBody.id() << std::endl;
//            }
//         }
//      }
//   }
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//class GravityWidget : public QWidget
//{
//public:
//   GravityWidget(QWidget *parent = 0);
//   ~GravityWidget();
//
//   BodySimulation *m_sim;
//
//protected:
//   void paintEvent(QPaintEvent* paintEvent);
//   void drawVelocityVector(QPainter &painter, Body body);
//
//   QPointF simToDevice(QPointF simPosition);
//};
//
//GravityWidget::GravityWidget(QWidget*) : QWidget()
//{
//   // Setup the simulation
//   m_sim = new BodySimulation();
//   m_sim->addBody(25.0, Vector2D(0.0, 0.0), Vector2D(0.0, 0.0), true);
//   m_sim->addBody(5.0, Vector2D(100.0, 0.0), Vector2D(0.0, 50.0));
//
//   // Start a timer and hook the timestepping into this
//   QTimer *timer = new QTimer(this);
//   connect(timer, SIGNAL(timeout()), m_sim, SLOT(advance()));
//   //connect(timer, SIGNAL(timeout()), ballGraph, SLOT(nextAnimationFrame()));
//   timer->start(100);
//}
//
//GravityWidget::~GravityWidget()
//{
//}
//
//void GravityWidget::paintEvent(QPaintEvent*)
//{
//   // Get the painter for the widget
//   QPainter painter(this);
//   painter.setBrush(Qt::blue);
//
//   // Loop bodies in sim and draw them
//   for (auto body : m_sim->bodies())
//   {
//      //std::cout << "Drawing Body, radius = " << body.radius() << ", position = (" << body.position().x() << ", " << body.position().y() << ")" << std::endl;
//      QPointF centrePoint = simToDevice(QPointF(body.position().x(), body.position().y()));
//      //std::cout << "Drawing Body at screen coordinates = (" << centrePoint.rx() << ", " << centrePoint.rx() << ")" << std::endl;
//      painter.drawEllipse(centrePoint, (qreal)body.radius(), (qreal)body.radius());
//      // Draw velocity vector of body
//      drawVelocityVector(painter, body);
//   }
//}
//
//void GravityWidget::drawVelocityVector(QPainter& painter, Body body)
//{
//   QPointF startPoint(body.position().x(), body.position().y());
//   // First get velocity magnitude
//   double velMag = body.velocity().magnitude();
//   Vector2D velDir = body.velocity().normalise();
//   //std::cout << "Vel direction = (" << velDir.x() << ", " << velDir.y() << ")" << std::endl;
//   QPointF endPoint = startPoint + velMag*QPointF(velDir.x(), velDir.y());
//   //std::cout << "Vel vector start = (" << startPoint.rx() << ", " << startPoint.ry() << ")" << std::endl;
//   //std::cout << "Vel vector end = (" << endPoint.rx() << ", " << endPoint.ry() << ")" << std::endl;
//   painter.drawLine(simToDevice(startPoint), simToDevice(endPoint));
//}
//
//QPointF GravityWidget::simToDevice(QPointF simPosition)
//{
//   return QPointF(simPosition.rx() + (this->height() / 2.0), simPosition.ry() + (this->width() / 2.0));
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//int main(int argc, char *argv[])
//{
//   QApplication app(argc, argv);
//   GravityWidget widget;
//   widget.resize(1024, 768);
//   widget.show();
//
//   return app.exec();
//}
