#pragma once
#include <cstdint>
#include <QtWebSockets/QWebSocketServer.h>


class Socket:public QObject
{
  Q_OBJECT

  public:
    Socket(uint16_t port);

  public Q_SIGNALS:
    void closed();

  private Q_SLOTS:
    void 	acceptError(QAbstractSocket::SocketError socketError);
    void 	closed();
    void 	newConnection();
    void 	originAuthenticationRequired(QWebSocketCorsAuthenticator *authenticator);
    void 	peerVerifyError(const QSslError &error);
    void 	preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator);
    void 	serverError(QWebSocketProtocol::CloseCode closeCode);
    void 	sslErrors(const QList<QSslError> &errors);

  private:
    QWebSocketServer* mpServer;
};
