#pragma once
#include "config.h"
#include <QApplication>
#include <memory>
#include <qtimer.h>
#include <queue>

class MainWindow;

namespace image
{
class ImageData;
}

namespace app
{
class App : public QObject
{
    Q_OBJECT

public:
    App(int argc, char* argv[]);

    int run();

    void run_command(const core::GenericCommand& cmd);
    void run_macro(const core::macro& macro);

private:
    void handle_error(const core::Error& error, const char* id);
    void setup_app_commands();
    void setup_testing();
    void exit(int value);
    void test();
    std::unique_ptr<QApplication>     _app;
    std::unique_ptr<image::ImageData> _image;
    std::unique_ptr<MainWindow>       _window;
    std::unique_ptr<QTimer>           _timer;
    const core::Config&               _config;

    bool                        _testmode = false;
    std::queue<core::CommandID> _testCommands;
};
} // namespace app