TEMPLATE = app
QT = gui core network xml
CONFIG += qt warn_on release
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/settingsdialog.ui
HEADERS = src/mainimpl.h \
 src/xmlrpc/client.h \
 src/xmlrpc/qxmlrpc_documentation.h \
 src/xmlrpc/request.h \
 src/xmlrpc/response.h \
 src/xmlrpc/server.h \
 src/xmlrpc/server_private.h \
 src/xmlrpc/serverintrospection.h \
 src/xmlrpc/stable.h \
 src/xmlrpc/variant.h \
 src/rtorrent/rgeneric.h \
 src/rtorrent/rsystem.h \
 src/rtorrent/rtorrent.h \
 src/rtorrent/rtorrentclient.h \
 src/rtorrent/rtorrentio.h \
 src/rtorrent/rtorrents.h \
 src/infoaction.h \
 src/traymenu.h \
 src/rtorrent/ritorrent.h \
 src/settingsdialog.h
SOURCES = src/mainimpl.cpp \
 src/main.cpp \
 src/xmlrpc/client.cpp \
 src/xmlrpc/request.cpp \
 src/xmlrpc/response.cpp \
 src/xmlrpc/server.cpp \
 src/xmlrpc/serverintrospection.cpp \
 src/xmlrpc/variant.cpp \
 src/rtorrent/rgeneric.cpp \
 src/rtorrent/rsystem.cpp \
 src/rtorrent/rtorrent.cpp \
 src/rtorrent/rtorrentclient.cpp \
 src/rtorrent/rtorrentio.cpp \
 src/rtorrent/rtorrents.cpp \
 src/infoaction.cpp \
 src/traymenu.cpp \
 src/rtorrent/ritorrent.cpp \
 src/settingsdialog.cpp
TRANSLATIONS += Resources/rwin_ru.ts
RESOURCES += Resources/res.qrc
