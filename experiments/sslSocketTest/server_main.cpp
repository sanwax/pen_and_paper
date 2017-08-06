#include <iostream>
#include <QtCore/QFile>
#include <QtCore/QByteArray>
#include <QtCore/QCoreApplication>
#include <QtNetwork/QSslKey>
#include <QtNetwork/QSslCertificate>
#include "Server.h"


int
main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
	// read certificate
	QList<QSslCertificate> certList = QSslCertificate::fromPath("server.crt");
	if (certList.length() < 1)
	{
		qDebug() << "[MAIN] Unable to load server certificate.";
		return 1;
	}
	qDebug() << "[MAIN] Using server certificate:";
	qDebug() << "[MAIN]--------------------------";
	std::cout << certList.first().toText().toStdString() << std::endl;
	//read private key
	QFile keyFile("server.key");
	keyFile.open(QIODevice::ReadOnly);
	const QByteArray privKeyRaw = keyFile.readAll();
	const QSslKey privKey = QSslKey(privKeyRaw, QSsl::Rsa);
	keyFile.close();
	qDebug() << "[MAIN]--------------------------";
	Server sock(certList.first(), privKey, 9090);
	return app.exec();
}
