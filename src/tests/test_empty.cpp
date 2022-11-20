#include "process.h"
#include "config.h"
#include "labels.h"
#include "app_commands.h"

#include <gtest/gtest.h>

TEST(TestEmpty, Empty)
{
    {
        std::vector<core::CommandID> ids;
        core::get_commands(ids);
        ASSERT_TRUE(ids.empty());
    }
    {
        const auto& conf = core::get_config();
        ASSERT_TRUE(conf.appCommands.empty());
        ASSERT_TRUE(conf.buttons.empty());
        ASSERT_TRUE(conf.macros.empty());
        ASSERT_TRUE(conf.menu.empty());
    }
    {
        ASSERT_STREQ(core::get_label("cmd.abc"), "???");
    }
}
