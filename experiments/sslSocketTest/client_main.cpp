#include <QtCore/QCoreApplication>
#include "Client.h"


int
main(int argc, char** argv)
{
	QCoreApplication app(argc,argv);
	Client c("127.0.0.1",9090);
	return app.exec();
}
