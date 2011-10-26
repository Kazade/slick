#ifndef NAVI_BAR_H
#define NAVI_BAR_H

#include <gtkmm.h>
#include "frontend/directory_menu.h"

/*
    NaviBar my_bar;
    
    my_bar.set_browser_root("~/Documents");
    my_bar.refresh_browser();
    
    my_bar.add_opened_file("~/Documents/my_program.py");
    my_bar.mark_file_changed("~/Documents/my_program.py");
*/

class NaviBar : public Gtk::MenuBar {
public:
    NaviBar();
    
    void set_browser_root(const std::string& path);
    void refresh_browser();

    void add_opened_file(const std::string& file_path);
    void remove_opened_file(const std::string& file_path);
    
    void mark_file_changed(const std::string& file_path, bool value=true);
    
    sigc::signal<void, std::string>& signal_browser_file_activated();
    sigc::signal<void, std::string>& signal_opened_file_activated();
    
private:
    std::string browser_root_;

    std::map<std::string, Gtk::MenuItem*> browser_entries_by_path_;
    std::map<std::string, Gtk::MenuItem*> opened_files_by_path_;

    DirectoryMenu* directory_menu_;
    
    Gtk::MenuItem opened_files_;
    Gtk::Menu opened_files_menu_;
    
    std::string get_name_from_path(const std::string& path);
};

#endif
