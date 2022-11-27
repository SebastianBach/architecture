#pragma once

#include "display.h"
#include "error.h"
#include "image_data.h"
#include <QTextEdit.h>
#include <QtWidgets/QMainWindow>
#include <qgridlayout.h>
#include <qmenubar.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(image::Image& img, QWidget* parent = Q_NULLPTR);
    ~MainWindow();

    void update_display();

    void add_to_log(QString msg);

    image::Image&  _image;
    DisplayWidget* _display;
    QGridLayout*   _mainLayout;
    QMenuBar*      _menuBar;
    QGridLayout*   _buttons;
    QTextEdit*     _log = nullptr;
};
