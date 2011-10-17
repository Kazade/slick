#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include <gtksourceviewmm.h>

class MainWindow {
private:
    Gtk::Window* window_;
    Gsv::View* source_view_; 
    
    Gtk::VBox main_layout_;
    
    Gtk::Toolbar toolbar_;

    Gtk::ToolButton new_;
    Gtk::ToolButton open_;
    Gtk::ToolButton save_;
    
    void create_toolbar();
    
    Gtk::MenuBar nav_bar_;
    Gtk::MenuItem nav_bar_directory_;
    Gtk::Menu nav_bar_browse_menu_;
    
    void populate_navbar(const std::string& path);
public:
    MainWindow();
    ~MainWindow();
    
    void on_quit();
    bool on_delete_event(GdkEventAny* event); 
};

#endif
