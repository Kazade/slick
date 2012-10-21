#include "navi_bar.h"

#include "kazbase/os/path.h"
#include "kazbase/logging/logging.h"
#include "backend/tree_walker.h"
#include "kazbase/list_utils.h"

NaviBar::NaviBar():
    directory_menu_(nullptr) {
    set_browser_root(os::path::expand_user("~"));
}

void NaviBar::set_browser_root(const std::string& path) {
    browser_root_ = path;
    refresh_browser();
}

void NaviBar::add_opened_file(const std::string& path) {
    if(container::contains(opened_files_by_path_, path)) {
        L_WARN("Attempted to add a path to the navi_bar twice");
        return;
    }

    opened_files_by_path_[path] = new Gtk::MenuItem(os::path::split(path).second);
    opened_files_menu_.append(*opened_files_by_path_[path]);

    //FIXME: sort alphabetically
}

void NaviBar::refresh_browser() {
    if(directory_menu_) {
        L_DEBUG("Removing and recreating the directory menu");
        remove(*directory_menu_);
        directory_menu_ = nullptr;
    }

    L_DEBUG("Creating a directory menu");
    directory_menu_ = Gtk::manage(new DirectoryMenu(browser_root_));
    directory_menu_->signal_change_directory_clicked().connect(sigc::mem_fun(this, &NaviBar::on_change_directory_clicked));

    L_DEBUG("Adding to the menu bar");
    append(*directory_menu_);
}

void NaviBar::on_directory_selected(Gtk::FileChooserDialog* dlg, int response) {
    if(response == Gtk::RESPONSE_OK) {
        set_browser_root(dlg->get_filename());
        refresh_browser();
    }
}

void NaviBar::on_change_directory_clicked() {
    L_DEBUG("Showing change directory dialog");
    Gtk::FileChooserDialog dialog("Select a project directory", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_modal(true);
    dialog.set_default_response(Gtk::RESPONSE_OK);
    dialog.signal_response().connect(sigc::bind<0>(sigc::mem_fun(this, &NaviBar::on_directory_selected), &dialog));
    dialog.show();
}
