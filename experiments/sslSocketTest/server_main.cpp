#include <QtCore/QCoreApplication>
#include "Server.h"


int
main(int argc, char** argv)
{
  QCoreApplication app(argc,argv);
  Server sock(9090);
  return app.exec();
}
