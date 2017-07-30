#include <cassert>
#include "Server.h"
#include <QtCore/QDebug>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QAbstractSocket>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketCorsAuthenticator>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>


Server::Server(uint16_t port)
{
	//setup server
	mpSocket = new QWebSocketServer(QStringLiteral("Test Server"), QWebSocketServer::SecureMode, this);
	//setup signals & slots
	QObject::connect(mpSocket, &QWebSocketServer::acceptError, this, &Server::acceptError);
	QObject::connect(mpSocket, &QWebSocketServer::closed, this, &Server::closed);
	QObject::connect(mpSocket, &QWebSocketServer::newConnection, this, &Server::newConnection);
	QObject::connect(mpSocket, &QWebSocketServer::originAuthenticationRequired, this, &Server::originAuthenticationRequired);
	QObject::connect(mpSocket, &QWebSocketServer::peerVerifyError, this, &Server::peerVerifyError);
	QObject::connect(mpSocket, &QWebSocketServer::preSharedKeyAuthenticationRequired, this, &Server::preSharedKeyAuthenticationRequired);
	QObject::connect(mpSocket, &QWebSocketServer::serverError, this, &Server::serverError);
	QObject::connect(mpSocket, &QWebSocketServer::sslErrors, this, &Server::sslErrors);
	//start listen server
	qDebug() << "Start listening on port " << port;
	auto res = mpSocket->listen(QHostAddress::Any, port);
	assert(res);
}

void
Server::acceptError(QAbstractSocket::SocketError socketError)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__ << "(" << socketError << ")";
}

void
Server::closed()
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
	emit socketClosed();
}

void
Server::newConnection()
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
	QWebSocket *pSock = mpSocket->nextPendingConnection();
	//connect signals & slots
	QObject::connect(pSock,&QWebSocket::aboutToClose,this,&Server::socketAboutToClose);
	QObject::connect(pSock,&QWebSocket::binaryFrameReceived,this,&Server::socketBinaryFrameReceived);
	QObject::connect(pSock,&QWebSocket::binaryMessageReceived,this,&Server::socketBinaryMessageReceived);
	QObject::connect(pSock,&QWebSocket::bytesWritten,this,&Server::socketBytesWritten);
	QObject::connect(pSock,&QWebSocket::connected,this,&Server::socketConnected);
	QObject::connect(pSock,&QWebSocket::disconnected,this,&Server::socketDisconnected);
	QObject::connect(pSock,static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),this,&Server::socketError);
	QObject::connect(pSock,&QWebSocket::pong,this,&Server::socketPong);
	QObject::connect(pSock,&QWebSocket::preSharedKeyAuthenticationRequired,this,&Server::socketPreSharedKeyAuthenticationRequired);
	QObject::connect(pSock,&QWebSocket::proxyAuthenticationRequired,this,&Server::socketProxyAuthenticationRequired);
	QObject::connect(pSock,&QWebSocket::readChannelFinished,this,&Server::socketReadChannelFinished);
	QObject::connect(pSock,&QWebSocket::sslErrors,this,&Server::socketSslErrors);
	QObject::connect(pSock,&QWebSocket::stateChanged,this,&Server::socketStateChanged);
	QObject::connect(pSock,&QWebSocket::textFrameReceived,this,&Server::socketTextFrameReceived);
	QObject::connect(pSock,&QWebSocket::textMessageReceived,this,&Server::socketTextMessageReceived);
	//enlist socket
	mClientList << pSock;
}

void
Server::originAuthenticationRequired(QWebSocketCorsAuthenticator *authenticator)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
}


void
Server::peerVerifyError(const QSslError &error)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
}


void
Server::preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
}


void
Server::serverError(QWebSocketProtocol::CloseCode closeCode)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
}


void
Server::sslErrors(const QList<QSslError> &errors)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketAboutToClose()
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketBinaryFrameReceived(const QByteArray &frame, bool isLastFrame)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketBinaryMessageReceived(const QByteArray &message)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketBytesWritten(qint64 bytes)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketConnected()
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketDisconnected()
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketError(QAbstractSocket::SocketError error)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketPong(quint64 elapsedTime, const QByteArray &payload)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketPreSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketReadChannelFinished()
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketSslErrors(const QList<QSslError> &errors)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketStateChanged(QAbstractSocket::SocketState state)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketTextFrameReceived(const QString &frame, bool isLastFrame)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::socketTextMessageReceived(const QString &message)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}

