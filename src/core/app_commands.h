#pragma once
#include "error.h"
#include <functional>

namespace core
{
struct AppCommandID
{
    explicit AppCommandID(const char* id) : _id(id) {}
    const char* const _id;
};



using AppCommandFunction = std::function<ReturnVoid()>;

void set_app_function(AppCommandID id, AppCommandFunction func);

ReturnVoid process_app_function(AppCommandID id);

} // namespace core
