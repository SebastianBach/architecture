#include "main_window.h"
#include "app_commands.h"
#include "config.h"
#include "get_app_name.h"
#include "process.h"
#include "register.h"
#include "ui_modules.h"
#include "utility.h"
#include <QMessageBox>
#include <qlayout.h>
#include <qmenubar.h>

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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    const auto& config = core::get_config();
    const auto w       = config.width;
    const auto h       = config.height;

    _data = std::make_unique<image::ImageData>(w, h);

    this->setWindowTitle(make_title_string());

    _mainLayout = new QGridLayout;

    auto menuBar = new QMenuBar;
    _mainLayout->setMenuBar(menuBar);

    auto* buttons = new QGridLayout;

    create_ui_modules(this, menuBar, buttons, config);

    _mainLayout->setSpacing(10);
    _mainLayout->setColumnMinimumWidth(0, 100);
    _mainLayout->setColumnMinimumWidth(1, w);
    _mainLayout->setRowMinimumHeight(0, h);

    _mainLayout->addLayout(buttons, 0, 0, Qt::AlignTop);

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
    _display->drawImage(*_data->get_image());
}

void MainWindow::add_to_log(QString msg)
{
    if (_log)
        _log->setText(_log->toPlainText() + "\n" + msg);
}

void MainWindow::show_error_dialog(core::Error& error, const char* id)
{
    QString msg{"Error executing command "};
    msg += id;
    msg += "\n";
    msg += convert_error(error);

    QMessageBox::critical(nullptr, "Error", msg);
}