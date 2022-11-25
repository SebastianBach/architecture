#include "image.h"
#include "register.h"
#include <cstdlib>
#include <ctime>

namespace
{
core::ReturnVoid trigger_error(image::Image* img)
{
    return core::Error{"Error from trigger_error()", core::Error::TYPE::TEST};
}

REGISTER_COMMAND(trigger_error, "cmd.dev.error", "Trigger Error")

} // namespace
