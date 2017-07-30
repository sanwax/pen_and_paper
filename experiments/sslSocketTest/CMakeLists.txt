QT5_WRAP_CPP(MOC_SOURCES_SERVER
	Server.h
	)

#QT5_WRAP_UI(UI_SOURCES
#)

#QT5_ADD_RESOURCES(QRC_SOURCES
#	)


set(SOURCE_FILES_SERVER
	${MOC_SOURCES_SERVER}
	server_main.cpp
	Server.cpp
	Server.h)

add_executable(exSslSocketServer ${SOURCE_FILES_SERVER})
QT5_USE_MODULES(exSslSocketServer Core Network WebSockets)

###############################################################################


QT5_WRAP_CPP(MOC_SOURCES_CLIENT
	Client.h
	)

#QT5_WRAP_UI(UI_SOURCES
#)

#QT5_ADD_RESOURCES(QRC_SOURCES
#	)


set(SOURCE_FILES_CLIENT
	${MOC_SOURCES_CLIENT}
	client_main.cpp
	Client.cpp
	Client.h
	)

add_executable(exSslSocketClient ${SOURCE_FILES_CLIENT})
QT5_USE_MODULES(exSslSocketClient Core Network WebSockets)




