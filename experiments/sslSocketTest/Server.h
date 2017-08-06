#pragma once

#include <cstdint>
#include <QtCore/QObject>
#include <QtNetwork/QSslCertificate>
#include <QtWebSockets/QWebSocketServer>


class Server : public QObject
{
		Q_OBJECT

	public:
		Server(const QSslCertificate& cert,const QSslKey& key, uint16_t port);


	signals:
		void socketClosed();


	private	slots:
		//slots of the socket server
		void acceptError(QAbstractSocket::SocketError socketError);

		void closed();

		void newConnection();

		void originAuthenticationRequired(QWebSocketCorsAuthenticator *authenticator);

		void peerVerifyError(const QSslError &error);

		void preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator);

		void serverError(QWebSocketProtocol::CloseCode closeCode);

		void sslErrors(const QList <QSslError> &errors);


		//slots of any web socket
		void clientAboutToClose();
		void clientBinaryFrameReceived(const QByteArray &frame, bool isLastFrame);
		void clientBinaryMessageReceived(const QByteArray &message);
		void clientBytesWritten(qint64 bytes);
		void clientConnected();
		void clientDisconnected();
		void clientError(QAbstractSocket::SocketError error);
		void clientPong(quint64 elapsedTime, const QByteArray &payload);
		void clientPreSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator);
		void clientProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
		void clientReadChannelFinished();
		void clientSslErrors(const QList<QSslError> &errors);
		void clientStateChanged(QAbstractSocket::SocketState state);
		void clientTextFrameReceived(const QString &frame, bool isLastFrame);
		void clientTextMessageReceived(const QString &message);

	private:
		QWebSocketServer *mpListenSocket;
		QList<QWebSocket*> mClientList;
};
