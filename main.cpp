#include <unistd.h>
#include "mainWindow.hpp"
#include "PSMC.hpp"

bool updateFunc(PSMC::ControllerManager *controllerManager)
{
    controllerManager->Update();
    return true;
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("pl.nadwey.psmoveclicker");
    Gtk::Settings::get_default()->property_gtk_application_prefer_dark_theme() = true;

    PSMC::ControllerManager controllerManager;
    Input::Input input;

    controllerManager.Start();

    auto updateFuncLambda = [&]()
    { return updateFunc(&controllerManager); };

    Glib::signal_idle().connect(updateFuncLambda);

    return app->make_window_and_run<MainWindow>(argc, argv);
}
