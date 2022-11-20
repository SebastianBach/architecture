#include "config.h"
#include "error.h"
#include "exports.h"
#include "get_app_name.h"
#include "image_data.h"
#include "process.h"
#include <iostream>

void print_info()
{
    std::cout << app::get_app_name();
    std::cout << " ";
    std::cout << app::get_app_version();
    std::cout << " ";
    std::cout << app::get_compile_date();
}

static constexpr auto RETURN_OK    = 0;
static constexpr auto RETURN_ERROR = 1;

inline auto print_error(const char* msg)
{
    std::cout << msg;
    return RETURN_ERROR;
}

inline void print(const char* msg)
{
    std::cout << msg << "\n";
}

core::ReturnVoid process(int argc, char* argv[])
{
    const char* file_path   = argv[1];
    const char* file_format = argv[2];

    print(file_path);
    print(file_format);

    const auto& c = core::get_config();

    image::ImageData img{c.width, c.height};

    for (auto i = 3; i < argc; ++i)
    {
        print(argv[i]);

        const auto res = core::process_command(core::CommandID{argv[i]}, img.get_image());
        if (!res)
            return res;
    }

    return core::export_image(core::ExportID{file_format, ""}, file_path, *img.get_image());
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        print_info();
        return RETURN_OK;
    }

    if (argc < 4)
        return print_error("Invalid argument count.");

    const auto res = process(argc, argv);
    if (res.isError())
        return print_error(res.getError().msg);

    return RETURN_OK;
}
