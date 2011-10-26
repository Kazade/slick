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
    
    L_DEBUG("Adding to the menu bar");
    append(*directory_menu_);
}
