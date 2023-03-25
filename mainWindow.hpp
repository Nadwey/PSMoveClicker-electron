#pragma once

#ifndef GTKMM_EXAMPLE_MAINWINDOW_H
#define GTKMM_EXAMPLE_MAINWINDOW_H

#include <gtkmm.h>
#include <memory>

class MainWindow : public Gtk::Window
{

public:
    MainWindow();

protected:
    Gtk::Box box;
    Gtk::CheckButton adofaiModeButton;
    Gtk::ListBox controllersListBox;

private:
    void on_row_clicked(Gtk::ListBoxRow* row);
    void on_adofaiBtn_toggled();

    class ListItem : public Gtk::ListBoxRow
    {
    public:
        ListItem(const std::string text);

    private:

        Gtk::Label label;
    };
};

#endif