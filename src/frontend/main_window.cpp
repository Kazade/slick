#include "main_window.h"

#include "kazbase/os/path.h"
#include "backend/tree_walker.h"

MainWindow::MainWindow():
    window_(nullptr),
    source_view_(nullptr) {

    window_ = new Gtk::Window();
    source_view_ = Gtk::manage(new Gsv::View());
    
    source_view_->set_show_line_numbers(true);
    source_view_->set_tab_width(4);
    source_view_->set_auto_indent(true);
    source_view_->set_insert_spaces_instead_of_tabs(true);
    source_view_->set_highlight_current_line(true);
//    source_view_->set_draw_spaces(true);
    
    source_view_->override_font(Pango::FontDescription("monospace"));

    main_viewport_.add(*source_view_);

    source_pane_.pack_start(nav_bar_, false, false);
    source_pane_.pack_start(main_viewport_);

    main_layout_.pack_start(toolbar_, false, false);
    main_layout_.pack_start(source_pane_);
    window_->add(main_layout_);

    window_->signal_delete_event().connect(sigc::mem_fun(this, &MainWindow::on_delete_event));
    window_->set_size_request(800, 600);

    create_toolbar();

    buffer_manager_.reset(new BufferManager(*source_view_));

    //populate_navbar(os::path::expand_user("~"));

/*    nav_bar_.append(nav_bar_directory_);
    nav_bar_directory_.set_submenu(nav_bar_browse_menu_);*/
    nav_bar_.get_directory_menu().signal_file_clicked().connect(sigc::mem_fun(this, &MainWindow::open_file));

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

/*
    TODO:
        Create a subclass of Gtk::MenuItem which is a lazy-submenu-populator, something like

        menu.append(LazyDirItem(path));

        which, on-draw adds a task to idle() that generates the submenu which may in turn
        add more LazyDirItems. This means the menu only loads the directories below the current level
        not all of them!
*/

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
    nav_bar_.set_browser_root(path);

}

void MainWindow::open_file(const std::string& filename) {
    L_DEBUG("Opening file: " + filename);
    BufferID buffer = buffer_manager_->open_file(filename);
    buffer_manager_->set_active_buffer(buffer);
}
