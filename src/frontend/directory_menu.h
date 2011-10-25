#ifndef DIRECTORY_MENU_H
#define DIRECTORY_MENU_H

#include <gtkmm.h>

class DirectoryMenu : Gtk::MenuItem {
public:
    DirectoryMenu(const std::string& path);

    void build();
};

#endif
