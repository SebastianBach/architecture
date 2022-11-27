#include "app.h"
#include "main_window.h"

int main(int argc, char* argv[])
{
    app::App app{argc, argv};

    return app.run();
}
