#include "main_window.h"
#include "config.h"
#include "get_app_name.h"
#include <qlayout.h>

namespace
{
QString make_title_string()
{
    QString title{app::get_app_name()};
    title += " ";
    title += app::get_app_version();
    title += " (";
    title += app::get_compile_date();
    title += ")";

    return title;
}

} // namespace

MainWindow::MainWindow(image::Image& img, QWidget* parent)
    : _image(img), QMainWindow(parent)
{
    const auto& config = core::get_config();
    const auto w       = config.width;
    const auto h       = config.height;

    setWindowTitle(make_title_string());

    _mainLayout = new QGridLayout;

    _menuBar = new QMenuBar;
    _mainLayout->setMenuBar(_menuBar);

    _buttons = new QGridLayout;

    _mainLayout->setSpacing(10);
    _mainLayout->setColumnMinimumWidth(0, 100);
    _mainLayout->setColumnMinimumWidth(1, w);
    _mainLayout->setRowMinimumHeight(0, h);

    _mainLayout->addLayout(_buttons, 0, 0, Qt::AlignTop);

    _display = new DisplayWidget(this);
    _display->setMinimumSize(QSize(w, h));
    _display->setMaximumSize(QSize(w, h));

    _mainLayout->addWidget(_display, 0, 1, Qt::AlignTop);

    if (config.ui_show_log)
    {
        _log = new QTextEdit(this);
        _log->setMinimumSize(QSize(200, 200));
        _log->setMaximumSize(QSize(200, 200));
        _log->setReadOnly(true);

        _mainLayout->addWidget(_log, 1, 1, Qt::AlignTop);
    }

    auto widget = new QWidget();
    widget->setLayout(_mainLayout);
    setCentralWidget(widget);

    update_display();
}

MainWindow::~MainWindow() {}

void MainWindow::update_display()
{
    _display->drawImage(_image);
}

void MainWindow::add_to_log(QString msg)
{
    if (_log)
        _log->setText(_log->toPlainText() + "\n" + msg);
}
