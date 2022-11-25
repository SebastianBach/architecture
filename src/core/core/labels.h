#pragma once

namespace core
{

void add_label(const char* id, const char* label);

const char* get_label(const char* id, const char* fallback = nullptr);
} // namespace core
