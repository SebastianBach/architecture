#include "process.h"
#include "ui_modules.h"
#include <qmenu.h>
#include <qmenubar.h>

namespace
{
void run_commands(std::vector<core::CommandID> ids, MainWindow* window)
{
    for (const auto& command : ids)
    {
        window->add_to_log(command._id);

        const auto res = core::process_command(command, window->_data->get_image());

        if (res.isError())
        {
            window->add_to_log(res.getError().msg);
            window->show_error_dialog(res.getError(), command._id);
            return;
        }
    }

    window->update_display();
}

static auto res = add_ui_module(100u,
    [](window_data& data)
    {
        if (data.config.macros.empty())
            return;

        auto entry = new QMenu(data.window->tr("Macros"), data.window);
        data.bar->addMenu(entry);

        for (auto& m : data.config.macros)
        {
            auto action = entry->addAction(m.name);
            auto ids    = m.commands;
            auto w      = data.window;
            data.window->connect(action, &QAction::triggered, [ids, w]() { run_commands(ids, w); });
        }
    });

} // namespace
