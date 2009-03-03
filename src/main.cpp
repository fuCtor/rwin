#include <QApplication>
#include <QTranslator>
#include "mainimpl.h"

//
int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
    QCoreApplication::setOrganizationName("aJIeks");
    QCoreApplication::setOrganizationDomain("aJIeks.org.ru");
    QCoreApplication::setApplicationName("rWin");
	QApplication::setQuitOnLastWindowClosed(false);

	qRegisterMetaType<QVariant>("QVariant");
	qRegisterMetaType<xmlrpc::Variant>("xmlrpc::Variant");
	QTranslator myTranslator;
    myTranslator.load(":/lang/rwin_" + QLocale::system().name());
    app.installTranslator(&myTranslator);
	QTranslator qtTranslator;
    qtTranslator.load(":/lang/qt_" + QLocale::system().name());
    app.installTranslator(&qtTranslator);
	MainDialogImpl win;
	return app.exec();
}
