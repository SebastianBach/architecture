#include "app.h"
#include "ui_modules.h"
#include <qmenu.h>
#include <qmenubar.h>

namespace
{
static auto res = add_ui_module(
    100u,
    [](window_data& data)
    {
        if (data.config.macros.empty())
            return;

        auto* app = data.app;

        auto entry = new QMenu(data.window->tr("Macros"), data.window);
        data.bar->addMenu(entry);

        for (auto& m : data.config.macros)
        {
            auto action = entry->addAction(m.name);

            data.window->connect(action, &QAction::triggered,
                                 [&m, app]() { app->run_macro(m); });
        }
    });

} // namespace
