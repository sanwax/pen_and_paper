#include <cassert>
#include "Server.h"
#include "Helper.h"
#include <QtCore/QDebug>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QAbstractSocket>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketCorsAuthenticator>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>


Server::Server(const QSslCertificate& cert,const QSslKey& key, uint16_t port)
{
	//setup server
	mpListenSocket = new QWebSocketServer(QStringLiteral("Test Server"), QWebSocketServer::SecureMode, this);
	mpListenSocket->setServerName("My Server Name");
	auto sslConfig=mpListenSocket->sslConfiguration();
	sslConfig.setPreSharedKeyIdentityHint("PSK Identity Hint");
	sslConfig.setProtocol(QSsl::SecureProtocols);
	sslConfig.setLocalCertificate(cert);
	sslConfig.setPrivateKey(key);
	sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);  //no peer certificate required - encrypted but untrusted
	mpListenSocket->setSslConfiguration(sslConfig);
	//setup signals & slots
	QObject::connect(mpListenSocket, &QWebSocketServer::acceptError, this, &Server::acceptError);
	QObject::connect(mpListenSocket, &QWebSocketServer::closed, this, &Server::closed);
	QObject::connect(mpListenSocket, &QWebSocketServer::newConnection, this, &Server::newConnection);
	QObject::connect(mpListenSocket, &QWebSocketServer::originAuthenticationRequired, this, &Server::originAuthenticationRequired);
	QObject::connect(mpListenSocket, &QWebSocketServer::peerVerifyError, this, &Server::peerVerifyError);
	QObject::connect(mpListenSocket, &QWebSocketServer::preSharedKeyAuthenticationRequired, this, &Server::preSharedKeyAuthenticationRequired);
	QObject::connect(mpListenSocket, &QWebSocketServer::serverError, this, &Server::serverError);
	QObject::connect(mpListenSocket, &QWebSocketServer::sslErrors, this, &Server::sslErrors);
	//start listen server
	auto res = mpListenSocket->listen(QHostAddress::Any, port);
	qDebug() << "[SERVER] Server URL = " << mpListenSocket->serverUrl();
	assert(res);
}

void
Server::acceptError(QAbstractSocket::SocketError socketError)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__ << " socketError = " << stringify(socketError);
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
	QWebSocket *pClientSocket = mpListenSocket->nextPendingConnection();
	//connect signals & slots
	QObject::connect(pClientSocket, &QWebSocket::aboutToClose, this, &Server::clientAboutToClose);
	QObject::connect(pClientSocket, &QWebSocket::binaryFrameReceived, this, &Server::clientBinaryFrameReceived);
	QObject::connect(pClientSocket, &QWebSocket::binaryMessageReceived, this, &Server::clientBinaryMessageReceived);
	QObject::connect(pClientSocket, &QWebSocket::bytesWritten, this, &Server::clientBytesWritten);
	QObject::connect(pClientSocket, &QWebSocket::connected, this, &Server::clientConnected);
	QObject::connect(pClientSocket, &QWebSocket::disconnected, this, &Server::clientDisconnected);
	QObject::connect(pClientSocket, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), this, &Server::clientError);
	QObject::connect(pClientSocket, &QWebSocket::pong, this, &Server::clientPong);
	QObject::connect(pClientSocket, &QWebSocket::preSharedKeyAuthenticationRequired, this, &Server::clientPreSharedKeyAuthenticationRequired);
	QObject::connect(pClientSocket, &QWebSocket::proxyAuthenticationRequired, this, &Server::clientProxyAuthenticationRequired);
	QObject::connect(pClientSocket, &QWebSocket::readChannelFinished, this, &Server::clientReadChannelFinished);
	QObject::connect(pClientSocket, &QWebSocket::sslErrors, this, &Server::clientSslErrors);
	QObject::connect(pClientSocket, &QWebSocket::stateChanged, this, &Server::clientStateChanged);
	QObject::connect(pClientSocket, &QWebSocket::textFrameReceived, this, &Server::clientTextFrameReceived);
	QObject::connect(pClientSocket, &QWebSocket::textMessageReceived, this, &Server::clientTextMessageReceived);
	//enlist socket
	mClientList << pClientSocket;
}

void
Server::originAuthenticationRequired(QWebSocketCorsAuthenticator *authenticator)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__ << " authenticator = " << authenticator;
}


void
Server::peerVerifyError(const QSslError &error)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__ << " sslError = " << error;
}


void
Server::preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
}


void
Server::serverError(QWebSocketProtocol::CloseCode closeCode)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__ << " closeCode = " << closeCode;
}


void
Server::sslErrors(const QList<QSslError> &errors)
{
	qDebug() << "[SERVER] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientAboutToClose()
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientBinaryFrameReceived(const QByteArray &frame, bool isLastFrame)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientBinaryMessageReceived(const QByteArray &message)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__ << " message = " << message;
}


void
Server::clientBytesWritten(qint64 bytes)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__ << " bytes = " << bytes;
}


void
Server::clientConnected()
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientDisconnected()
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientError(QAbstractSocket::SocketError error)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__ << " error = " << stringify(error);
}


void
Server::clientPong(quint64 elapsedTime, const QByteArray &payload)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientPreSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientReadChannelFinished()
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientSslErrors(const QList<QSslError> &errors)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientStateChanged(QAbstractSocket::SocketState state)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__ << " state = " << state;
}


void
Server::clientTextFrameReceived(const QString &frame, bool isLastFrame)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__;
}


void
Server::clientTextMessageReceived(const QString &message)
{
	qDebug() << "[SOCKET " << sender() << "] Passing " << __PRETTY_FUNCTION__ << " message = " << message;
	QWebSocket *pClient = dynamic_cast<QWebSocket *>(sender());
	Q_ASSERT(pClient);
	if (pClient)
	{
		pClient->sendTextMessage("Hello Moon");
	}
}

