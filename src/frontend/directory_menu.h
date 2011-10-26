#ifndef DIRECTORY_MENU_H
#define DIRECTORY_MENU_H

#include <gtkmm.h>
#include <string>

class DirectoryMenu : public Gtk::MenuItem {
public:
    DirectoryMenu(const std::string& path, bool is_root=true);

    bool build(Cairo::RefPtr<Cairo::Context> context);
    
private:
    std::string path_;
    bool built_;
    bool is_root_;
};

#endif
