#include <QtCore/QCoreApplication>
#include "Socket.h"


int
int main(int argc, char const *argv[])
{
  QCoreApplication app(argc,argv);
  Socket sock(9090);
  QObject::connect(&sock,&Socket::closed,&app,&QCoreApplication::exit);
  return app.exec();
}
