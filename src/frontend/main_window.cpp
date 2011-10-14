#include "main_window.h"

MainWindow::MainWindow():
    window_(NULL) {

    window_ = new Gtk::Window();
    
    window_->signal_delete_event().connect(sigc::mem_fun(this, &MainWindow::on_delete_event));
    window_->show_all();
}

void MainWindow::on_quit() {
    Gtk::Main::quit();
}

bool MainWindow::on_delete_event(GdkEventAny* event) {
    on_quit();
    return false;
}
