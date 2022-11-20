#include "exports.h"
#include "process.h"
#include "ui_modules.h"
#include <qfiledialog.h>
#include <qmenu.h>
#include <qmenubar.h>

namespace
{
void run_export(core::ExportID id, MainWindow* window)
{
    window->add_to_log(id._id);

    auto filter = "Image File (*." + QString(id._suffix) + ")";

    const auto file = QFileDialog::getSaveFileName(nullptr, "Save Image", "", filter, &filter);
    if (file.isEmpty())
        return;

    const auto stdString = file.toStdString();
    auto filename        = stdString.c_str();

    window->add_to_log(filename);

    const auto res = core::export_image(id, filename, *(window->_data->get_image()));

    if (res.isError())
    {
        window->add_to_log(res.getError().msg);
        window->show_error_dialog(res.getError(), id._id);
    }
}

static auto res =
    add_ui_module(11u,
                  [](window_data& data)
                  {
                      std::vector<core::ExportID> ids;
                      core::get_export_formats(ids);

                      if (ids.empty())
                          return;

                      auto window = data.window;
                      auto bar    = data.bar;

                      auto exportMenu = new QMenu(window->tr("Export"), window);
                      bar->addMenu(exportMenu);

                      for (const auto id : ids)
                      {
                          auto action = exportMenu->addAction(id._id);

                          window->connect(action, &QAction::triggered, [id, window]() { run_export(id, window); });
                      }
                  });
} // namespace
