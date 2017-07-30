#pragma once

#include <cstdint>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocketServer>


class Server : public QObject
{
		Q_OBJECT

	public:
		Server(uint16_t port);


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
		void socketAboutToClose();
		void socketBinaryFrameReceived(const QByteArray &frame, bool isLastFrame);
		void socketBinaryMessageReceived(const QByteArray &message);
		void socketBytesWritten(qint64 bytes);
		void socketConnected();
		void socketDisconnected();
		void socketError(QAbstractSocket::SocketError error);
		void socketPong(quint64 elapsedTime, const QByteArray &payload);
		void socketPreSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator);
		void socketProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
		void socketReadChannelFinished();
		void socketSslErrors(const QList<QSslError> &errors);
		void socketStateChanged(QAbstractSocket::SocketState state);
		void socketTextFrameReceived(const QString &frame, bool isLastFrame);
		void socketTextMessageReceived(const QString &message);

	private:
		QWebSocketServer *mpSocket;
		QList<QWebSocket*> mClientList;
};
