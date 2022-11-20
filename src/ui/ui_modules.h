#pragma once
#include <functional>

#include "config.h"
#include "main_window.h"

class MainWindow;
class QMenuBar;
class QGridLayout;

struct window_data
{
    MainWindow* window;
    QMenuBar* bar;
    QGridLayout* button_area;
    const core::Config& config;
};

using UI_MODULE_FUNC = std::function<void(window_data&)>;

bool add_ui_module(unsigned int order, UI_MODULE_FUNC);

void create_ui_modules(MainWindow*, QMenuBar*, QGridLayout*, const core::Config&);
