#pragma once
#include <QtNetwork/QAbstractSocket>


#define _CASE_BLOCK(X)\
	case X: { return QString(#X); }


QString
stringify(QAbstractSocket::SocketError iError)
{
	switch (iError)
	{
		_CASE_BLOCK(QAbstractSocket::ConnectionRefusedError)
		_CASE_BLOCK(QAbstractSocket::RemoteHostClosedError)
		_CASE_BLOCK(QAbstractSocket::HostNotFoundError)
		_CASE_BLOCK(QAbstractSocket::SocketAccessError)
		_CASE_BLOCK(QAbstractSocket::SocketResourceError)
		_CASE_BLOCK(QAbstractSocket::SocketTimeoutError)
		_CASE_BLOCK(QAbstractSocket::DatagramTooLargeError)
		_CASE_BLOCK(QAbstractSocket::NetworkError)
		_CASE_BLOCK(QAbstractSocket::AddressInUseError)
		_CASE_BLOCK(QAbstractSocket::SocketAddressNotAvailableError)
		_CASE_BLOCK(QAbstractSocket::UnsupportedSocketOperationError)
		_CASE_BLOCK(QAbstractSocket::ProxyAuthenticationRequiredError)
		_CASE_BLOCK(QAbstractSocket::SslHandshakeFailedError)
		_CASE_BLOCK(QAbstractSocket::UnfinishedSocketOperationError)
		_CASE_BLOCK(QAbstractSocket::ProxyConnectionRefusedError)
		_CASE_BLOCK(QAbstractSocket::ProxyConnectionClosedError)
		_CASE_BLOCK(QAbstractSocket::ProxyConnectionTimeoutError)
		_CASE_BLOCK(QAbstractSocket::ProxyNotFoundError)
		_CASE_BLOCK(QAbstractSocket::ProxyProtocolError)
		_CASE_BLOCK(QAbstractSocket::OperationError)
		_CASE_BLOCK(QAbstractSocket::SslInternalError)
		_CASE_BLOCK(QAbstractSocket::SslInvalidUserDataError)
		_CASE_BLOCK(QAbstractSocket::TemporaryError)
		_CASE_BLOCK(QAbstractSocket::UnknownSocketError)
		default:
		{
			return QString("<unknown error code #%1>").arg(iError);
		}
	}
}
