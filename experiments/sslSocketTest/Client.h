#pragma once

#include <cstdint>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>


class Client : public QObject
{
	Q_OBJECT

	public:
		Client(QString sHost,uint16_t port);



	private	slots:
		//slots of any web socket
		void aboutToClose();
		void binaryFrameReceived(const QByteArray &frame, bool isLastFrame);
		void binaryMessageReceived(const QByteArray &message);
		void bytesWritten(qint64 bytes);
		void connected();
		void disconnected();
		void error(QAbstractSocket::SocketError error);
		void pong(quint64 elapsedTime, const QByteArray &payload);
		void preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator);
		void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
		void readChannelFinished();
		void sslErrors(const QList<QSslError> &errors);
		void stateChanged(QAbstractSocket::SocketState state);
		void textFrameReceived(const QString &frame, bool isLastFrame);
		void textMessageReceived(const QString &message);

		void
		connectServer();

	private:

		QWebSocket* mpSocket=nullptr;
		QUrl mUrl;
		int miConnectionAttempts=0;
		const int miMaxConnectionAttempts=2;
};
