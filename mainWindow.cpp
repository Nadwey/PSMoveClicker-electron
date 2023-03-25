#include "mainWindow.hpp"
#include <iostream>
#include "PSMC.hpp"

MainWindow::MainWindow() : adofaiModeButton("ADOFAI mode")
{
    set_title("PSMoveClicker v2.0.0-alpha.1");
    set_default_size(800, 550);
    set_child(box);

    // for (int i = 0; i < 10; i++)
    // {
    //     auto item = Gtk::make_managed<ListItem>("Test " + std::to_string(i));
    //     controllersListBox.append(*item);
    // }

    controllersListBox.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::on_row_clicked));
    adofaiModeButton.signal_toggled().connect(sigc::mem_fun(*this,
                                                            &MainWindow::on_adofaiBtn_toggled));

    box.append(adofaiModeButton);
    // box.append(controllersListBox);
}

void MainWindow::on_row_clicked(Gtk::ListBoxRow *row)
{
    ListItem *item = dynamic_cast<ListItem *>(row);
}

void MainWindow::on_adofaiBtn_toggled()
{
    PSMC::ControllerManager::adofaiMode = adofaiModeButton.get_active();
}

MainWindow::ListItem::ListItem(const std::string text) : label(text)
{
    set_child(label);
}
