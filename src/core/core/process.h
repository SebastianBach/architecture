#pragma once

#include <vector>
#include "error.h"
#include "register.h"


namespace image
{
class Image;
}

namespace core
{
ReturnVoid process_command(const CommandID&id, image::Image* img);

void get_commands(std::vector<CommandID>&, const char* filter = nullptr);
}
