//
// Created by mayday on 30.07.17.
//

#include "Client.h"
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>


Client::Client(QString sHost, uint16_t port)
{
	//setup socket
	mpSocket = new QWebSocket();
	//connect signals & slots
	QObject::connect(mpSocket, &QWebSocket::aboutToClose, this, &Client::aboutToClose);
	QObject::connect(mpSocket, &QWebSocket::binaryFrameReceived, this, &Client::binaryFrameReceived);
	QObject::connect(mpSocket, &QWebSocket::binaryMessageReceived, this, &Client::binaryMessageReceived);
	QObject::connect(mpSocket, &QWebSocket::bytesWritten, this, &Client::bytesWritten);
	QObject::connect(mpSocket, &QWebSocket::connected, this, &Client::connected);
	QObject::connect(mpSocket, &QWebSocket::disconnected, this, &Client::disconnected);
	QObject::connect(mpSocket, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), this, &Client::error);
	QObject::connect(mpSocket, &QWebSocket::pong, this, &Client::pong);
	QObject::connect(mpSocket, &QWebSocket::preSharedKeyAuthenticationRequired, this, &Client::preSharedKeyAuthenticationRequired);
	QObject::connect(mpSocket, &QWebSocket::proxyAuthenticationRequired, this, &Client::proxyAuthenticationRequired);
	QObject::connect(mpSocket, &QWebSocket::readChannelFinished, this, &Client::readChannelFinished);
	QObject::connect(mpSocket, &QWebSocket::sslErrors, this, &Client::sslErrors);
	QObject::connect(mpSocket, &QWebSocket::stateChanged, this, &Client::stateChanged);
	QObject::connect(mpSocket, &QWebSocket::textFrameReceived, this, &Client::textFrameReceived);
	QObject::connect(mpSocket, &QWebSocket::textMessageReceived, this, &Client::textMessageReceived);
	//open socket
	mpSocket->open(QUrl(QString("https://%1:%2").arg(sHost).arg(port)));
}


//slots of any web socket
void Client::aboutToClose()
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::binaryFrameReceived(const QByteArray &frame, bool isLastFrame)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::binaryMessageReceived(const QByteArray &message)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::bytesWritten(qint64 bytes)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::connected()
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::disconnected()
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::error(QAbstractSocket::SocketError error)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__ << " error=" << (int) error;
}


void Client::pong(quint64 elapsedTime, const QByteArray &payload)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::readChannelFinished()
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::sslErrors(const QList<QSslError> &errors)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::stateChanged(QAbstractSocket::SocketState state)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::textFrameReceived(const QString &frame, bool isLastFrame)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::textMessageReceived(const QString &message)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}
