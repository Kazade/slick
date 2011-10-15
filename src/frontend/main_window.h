#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

class MainWindow {
private:
    Gtk::Window* window_;
    Gtk::Sourceview* source_view_; 
    
public:
    MainWindow();
    ~MainWindow();
    
    void on_quit();
    bool on_delete_event(GdkEventAny* event); 
};

#endif
