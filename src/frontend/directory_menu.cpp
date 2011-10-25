#include "directory_menu.h"

DirectoryMenu::DirectoryMenu(const std::string& path) {
    signal_draw().connect_once(sigc::mem_fun(this, &DirectoryMenu::build));
}

void DirectoryMenu::build() {
    for(std::string d: os::list_dir(path_)) {
        DirectoryMenu* new_menu = Gtk::manage(new DirectoryMenu(os::path::join(path_, d)));
        get_submenu->append(new_menu);
    }
}
