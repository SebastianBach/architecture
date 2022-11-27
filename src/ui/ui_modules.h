#pragma once
#include <functional>

#include "config.h"
#include "main_window.h"

class MainWindow;
class QMenuBar;
class QGridLayout;

namespace app
{
class App;
}

struct window_data
{
    app::App* app;
    MainWindow* window;
    QMenuBar* bar;
    QGridLayout* button_area;
    const core::Config& config;
};

using UI_MODULE_FUNC = std::function<void(window_data&)>;

bool add_ui_module(unsigned int order, UI_MODULE_FUNC);

void create_ui_modules(app::App*,MainWindow*, QMenuBar*, QGridLayout*, const core::Config&);
