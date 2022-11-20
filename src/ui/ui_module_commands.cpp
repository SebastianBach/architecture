#include "process.h"
#include "ui_modules.h"
#include <qmenu.h>
#include <qmenubar.h>

namespace
{
void run_command(core::CommandID id, MainWindow* window)
{
    window->add_to_log(id._id);

    const auto res = core::process_command(id, window->_data->get_image());

    if (res.isError())
    {
        window->add_to_log(res.getError().msg);
        window->show_error_dialog(res.getError(), id._id);
    }
    else
        window->update_display();
}

static auto res =
    add_ui_module(20u,
                  [](window_data& data)
                  {
                      auto window        = data.window;
                      const auto& config = data.config;
                      auto bar           = data.bar;

                      for (const auto& menu_element : config.menu)
                      {
                          auto entry = new QMenu(window->tr(menu_element.name), window);
                          bar->addMenu(entry);

                          for (const auto& command : menu_element.commands)
                          {
                              auto action   = entry->addAction(command.label);
                              const auto id = command.id;
                              window->connect(action, &QAction::triggered, [id, window]() { run_command(id, window); });
                          }
                      }
                  });

static auto resbuttons = add_ui_module(1000u,
                                       [](window_data& data)
                                       {
                                           auto window        = data.window;
                                           const auto& config = data.config;
                                           auto bar           = data.bar;
                                           auto grid          = data.button_area;

                                           auto offset       = 10;
                                           auto buttonOffset = 0;
                                           for (const auto& id : config.buttons)
                                           {
                                               auto* button = new QPushButton(id.name, window);
                                               button->setMinimumSize(QSize(200, 50));
                                               button->setMaximumSize(QSize(200, 50));
                                               offset += 50;

                                               grid->addWidget(button, buttonOffset, 0, Qt::AlignTop);
                                               buttonOffset++;
                                               auto command = id.command;
                                               window->connect(button, &QPushButton::released, window,
                                                               [command, window]() { run_command(command, window); });
                                           }
                                       });

} // namespace
