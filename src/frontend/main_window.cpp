#include "main_window.h"

#include "backend/tree_walker.h"

MainWindow::MainWindow():
    window_(nullptr),
    source_view_(nullptr) {

    window_ = new Gtk::Window();
    source_view_ = Gtk::manage(new Gsv::View());
    
    main_layout_.pack_start(toolbar_, false, false);
    main_layout_.pack_start(*source_view_);
    window_->add(main_layout_);
        
    window_->signal_delete_event().connect(sigc::mem_fun(this, &MainWindow::on_delete_event));
    window_->set_size_request(800, 600);
    
    create_toolbar();
    populate_navbar("~");
    
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

void MainWindow::create_toolbar() {
    new_.set_stock_id(Gtk::Stock::NEW);
    open_.set_stock_id(Gtk::Stock::OPEN);
    save_.set_stock_id(Gtk::Stock::SAVE);
    
    toolbar_.append(new_);
    toolbar_.append(open_);
    toolbar_.append(save_);
}

void MainWindow::populate_navbar(const std::string& path) {
/*
    [Home] 
    Change directory...
    ----------------
    Documents >
    Downloads >
    Projects > Engage >
               PotatoCI >
*/
    TreeWalker walker(path);
    TreeWalker::PathList files = walker.find_files();
    for(std::string f: files) {
        Gtk::MenuItem* item = Gtk::manage(new Gtk::MenuItem(f));
        nav_bar_browse_menu_.append(*item);
    }
}
