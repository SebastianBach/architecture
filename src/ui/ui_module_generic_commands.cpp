#include "app.h"
#include "ui_modules.h"
#include <qmenu.h>
#include <qmenubar.h>
#include <qpushbutton.h>

namespace
{
static auto res = add_ui_module(
    21u,
    [](window_data& data)
    {
        auto        window = data.window;
        const auto& config = data.config;
        auto        bar    = data.bar;
        auto*       app    = data.app;

        for (const auto& menu_element : config.generic_menus)
        {
            auto entry = new QMenu(window->tr(menu_element.name), window);
            bar->addMenu(entry);

            for (const auto& command : menu_element.commands)
            {
                auto action = entry->addAction(command.get_label());

                window->connect(action, &QAction::triggered,
                                [&command, app]()
                                { app->run_command(command); });
            }
        }
    });

static auto resbuttons = add_ui_module(
    50u,
    [](window_data& data)
    {
        auto        window = data.window;
        const auto& config = data.config;
        auto        grid   = data.button_area;
        auto*       app    = data.app;

        auto offset       = 10;
        auto buttonOffset = 0;
        for (const auto& id : config.generic_buttons)
        {
            auto* button = new QPushButton(id.get_label(), window);
            button->setMinimumSize(QSize(200, 50));
            button->setMaximumSize(QSize(200, 50));
            offset += 50;

            grid->addWidget(button, buttonOffset, 0, Qt::AlignTop);
            buttonOffset++;

            window->connect(button, &QPushButton::released, window,
                            [&id, app]() { app->run_command(id); });
        }
    });

} // namespace
