#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include <gtksourceviewmm.h>

#include "frontend/navi_bar.h"

class MainWindow {
private:
    Gtk::Window* window_;
    Gsv::View* source_view_; 
    
    Gtk::VBox main_layout_;
    Gtk::VBox source_pane_;
    
    Gtk::Toolbar toolbar_;

    Gtk::ToolButton new_;
    Gtk::ToolButton open_;
    Gtk::ToolButton save_;
    
    void create_toolbar();
    
    NaviBar nav_bar_;
    
    void populate_navbar(const std::string& path);
public:
    MainWindow();
    ~MainWindow();
    
    void on_quit();
    bool on_delete_event(GdkEventAny* event); 
};

#endif
