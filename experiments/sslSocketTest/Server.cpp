#include <cassert>
#include "Socket.h"
#include <QtCore/QDebug>
#include <QtNetwork/QAbstractSocket>
#include <QtWebSockets/QWebSocketCorsAuthenticator>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>


Socket::Socket(uint16_t port)
{
	//setup server
	mpServer = new QWebSocketServer(QStringLiteral("Test Server"), QWebSocketServer::SecureMode, this);
	//setup signals & slots
	QObject::connect(mpServer, &QWebSocketServer::acceptError, this, &Socket::acceptError);
	QObject::connect(mpServer, &QWebSocketServer::closed, this, &Socket::closed);
	QObject::connect(mpServer, &QWebSocketServer::newConnection, this, &Socket::newConnection);
	QObject::connect(mpServer, &QWebSocketServer::originAuthenticationRequired, this, &Socket::originAuthenticationRequired);
	QObject::connect(mpServer, &QWebSocketServer::peerVerifyError, this, &Socket::peerVerifyError);
	QObject::connect(mpServer, &QWebSocketServer::preSharedKeyAuthenticationRequired, this, &Socket::preSharedKeyAuthenticationRequired);
	QObject::connect(mpServer, &QWebSocketServer::serverError, this, &Socket::serverError);
	QObject::connect(mpServer, &QWebSocketServer::sslErrors, this, &Socket::sslErrors);
	//start listen server
	qDebug() << "Start listening on port " << port;
	auto res = mpServer->listen(QHostAddress::Any, port);
	assert(res);
}

void
Socket::acceptError(QAbstractSocket::SocketError socketError)
{
	qDebug() << "Passing " << __PRETTY_FUNCTION__ << "(" << socketError << ")";
}

void
Socket::closed()
{
	qDebug() << "Passing " << __PRETTY_FUNCTION__;
	emit socketClosed();
}

void
Socket::newConnection()
{
	qDebug() << "Passing " << __PRETTY_FUNCTION__;
	QWebSocket* pSock=mpServer->nextPendingConnection();
	mClientList<<pSock;
}

void
Socket::originAuthenticationRequired(QWebSocketCorsAuthenticator *authenticator)
{
	qDebug() << "Passing " << __PRETTY_FUNCTION__;
}


void
Socket::peerVerifyError(const QSslError &error)
{
	qDebug() << "Passing " << __PRETTY_FUNCTION__;
}


void
Socket::preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
	qDebug() << "Passing " << __PRETTY_FUNCTION__;
}


void
Socket::serverError(QWebSocketProtocol::CloseCode closeCode)
{
	qDebug() << "Passing " << __PRETTY_FUNCTION__;
}


void
Socket::sslErrors(const QList <QSslError> &errors)
{
	qDebug() << "Passing " << __PRETTY_FUNCTION__;
}
