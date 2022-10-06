#include "View_module/mainwindow.h"


#include <QApplication>
#include <QLocale>
#include <QTranslator>
using S21::MainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "3DViewer_v2_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    ModelFrame model;
    ViewerController controller(&model);
    MainWindow view(&controller);
    view.show();

    return a.exec();
}
