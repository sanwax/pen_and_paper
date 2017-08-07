//
// Created by mayday on 30.07.17.
//

#include <QtCore/QTimer>
#include <thread>
#include <chrono>
#include "Client.h"
#include "Helper.h"
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <thread>

using namespace std::chrono_literals;

Client::Client(QString sHost, uint16_t port)
{
	//setup socket
	mpSocket = new QWebSocket();
	//declare socket url
	mUrl = QUrl(QString("wss://%1:%2").arg(sHost).arg(port));
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
	QTimer::singleShot(1,this,SLOT(connectServer()));
}

void
Client::connectServer()
{
	std::this_thread::sleep_for(1s);
	miConnectionAttempts+=1;
	if (miConnectionAttempts>miMaxConnectionAttempts)
	{
		qDebug()<<"[SOCKET "<< mpSocket <<"] No more connection attempts.";
		return;
	}
	//try connect....
	qDebug() << "[SOCKET " << mpSocket << "] Opening " << mUrl << " attempt "<<miConnectionAttempts;
	qDebug() << "[SOCKET " << mpSocket << "] "<<mpSocket->sslConfiguration().caCertificates().length()<<" CA certs defined.";
	mpSocket->open(mUrl);
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
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__ << " bytes=" << bytes;
}


void Client::connected()
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
	std::this_thread::sleep_for(1s);
	qDebug() << "[SOCKET " << mpSocket << "] Sending ping ... ";
	mpSocket->ping(QByteArray("<<<ping>>>"));
}


void Client::disconnected()
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::error(QAbstractSocket::SocketError error)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__ << " error=" << stringify(error);
}


void Client::pong(quint64 elapsedTime, const QByteArray &payload)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__ << " elapsedTime = " << elapsedTime << " payload = " << payload;
	std::this_thread::sleep_for(1s);
	qDebug() << "[SOCKET " << mpSocket << "] Sending ping ... ";
	mpSocket->sendTextMessage("Hello World");
}


void Client::preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__ << "authenticator = " << authenticator;
	qDebug() << "[SOCKET " << mpSocket << "] PSK: Identity = " << authenticator->identity() << " hint=" << authenticator->identityHint();
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
	//fetch ssl configuration
	QSslConfiguration sslConfig=mpSocket->sslConfiguration();
	QList<QSslCertificate> caCerts=sslConfig.caCertificates();
	//walk errors
	int i=1;
	for (auto err:errors)
	{
		qDebug()<<"[SOCKET "<<mpSocket<<"] Error #"<<i<<": "<<err.errorString();
		qDebug()<<"[SOCKET "<<mpSocket<<"] Certificate CN: "<<err.certificate().subjectInfo(QSslCertificate::CommonName);
		++i;
		//assume user accepts certificate
		caCerts.append(err.certificate());
	}
	//change set of ca certficates
	sslConfig.setCaCertificates(caCerts);
	mpSocket->setSslConfiguration(sslConfig);
	//retry
	QTimer::singleShot(1,this,SLOT(connectServer()));
}


void Client::stateChanged(QAbstractSocket::SocketState state)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__ << " state = " << state;
}


void Client::textFrameReceived(const QString &frame, bool isLastFrame)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__;
}


void Client::textMessageReceived(const QString &message)
{
	qDebug() << "[SOCKET " << mpSocket << "] Passing " << __PRETTY_FUNCTION__ << " message = " << message;
	std::this_thread::sleep_for(1s);
	qDebug() << "[SOCKET " << mpSocket << "] Closing connection";
	mpSocket->close(QWebSocketProtocol::CloseCodeGoingAway, "Closing connection after message reception.");
}
