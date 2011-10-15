#include "main_window.h"

MainWindow::MainWindow():
    window_(nullptr),
    source_view_(nullptr) {

    window_ = new Gtk::Window();
    source_view_ = Gtk::manage(new Gtk::Sourceview());
    window_->add(*source_view_);
        
    window_->signal_delete_event().connect(sigc::mem_fun(this, &MainWindow::on_delete_event));
    window_->show_all();
}

MainWindow::~MainWindow() {
    delete window_;
}

void MainWindow::on_quit() {
    Gtk::Main::quit();
}

bool MainWindow::on_delete_event(GdkEventAny* event) {
    on_quit();
    return false;
}
