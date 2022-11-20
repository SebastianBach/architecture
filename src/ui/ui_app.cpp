#include "main_window.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication app{argc, argv};

    MainWindow window;
    window.showMaximized();

    return app.exec();
}
