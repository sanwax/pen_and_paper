#pragma once

#include <cstdint>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocketServer>


class Socket : public QObject
{
		Q_OBJECT

	public:
		Socket(uint16_t port);


	signals:
		void socketClosed();


	private	slots:
		void acceptError(QAbstractSocket::SocketError socketError);

		void closed();

		void newConnection();

		void originAuthenticationRequired(QWebSocketCorsAuthenticator *authenticator);

		void peerVerifyError(const QSslError &error);

		void preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator);

		void serverError(QWebSocketProtocol::CloseCode closeCode);

		void sslErrors(const QList <QSslError> &errors);

	private:
		QWebSocketServer *mpServer;
		QList<QWebSocket*> mClientList;
};
