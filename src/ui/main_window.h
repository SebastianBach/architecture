#pragma once

#include "display.h"
#include "image_data.h"
#include <QPushButton>
#include <QtWidgets/QMainWindow>
#include <memory>
#include <qgridlayout.h>
#include <QTextEdit.h>
#include "error.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();

    void update_display();

    void add_to_log(QString msg);
    void show_error_dialog(core::Error& error, const char* id);

    std::unique_ptr<image::ImageData> _data;

private:
    DisplayWidget* _display;

    QGridLayout* _mainLayout;

    QTextEdit* _log = nullptr;
};
