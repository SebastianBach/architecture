#include "ui_modules.h"
#include <algorithm>
#include <vector>
#include "app.h"

namespace
{
struct ui_module
{
    UI_MODULE_FUNC func;
    unsigned int order;
};

auto& get_ui_modules()
{
    static std::vector<ui_module> modules;
    return modules;
}

struct before
{
    bool operator()(const ui_module& x, const ui_module& y) const
    {
        return x.order < y.order;
    }
};
} // namespace

bool add_ui_module(unsigned int order, UI_MODULE_FUNC f)
{
    auto& modules = get_ui_modules();
    modules.push_back({f, order});
    return true;
}

void create_ui_modules(app::App*app,MainWindow* window, QMenuBar* bar, QGridLayout* buttons, const core::Config& config)
{
    auto& modules = get_ui_modules();

    std::sort(modules.begin(), modules.end(), before());

    window_data w{app, window, bar, buttons, config};

    for (auto& m : modules)
        m.func(w);
}
