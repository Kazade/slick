#include "navi_bar.h"

#include "kazbase/os/path.h"
#include "kazbase/logging/logging.h"
#include "backend/tree_walker.h"
#include "kazbase/list_utils.h"

NaviBar::NaviBar() {
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
    TreeWalker walker(browser_root_);
    
    for(TreeWalker::Level l: walker.walk()) {
        if(!container::contains(browser_entries_by_path_, l.root)) {
            //Create a directory entry for the root if it doesn't exist
            browser_entries_by_path_[l.root] = new Gtk::MenuItem(os::path::split(l.root).second);            
            Gtk::Menu* mnu = Gtk::manage(new Gtk::Menu());
            browser_entries_by_path_[l.root]->set_submenu(*mnu);
        }
        
        for(std::string d: l.dirs) {
            //For each directory, create a Gtk::MenuItem and a submenu
            std::string path = os::path::join(l.root, d);
            browser_entries_by_path_[path] = new Gtk::MenuItem(d);            
            browser_entries_by_path_[l.root]->get_submenu()->append(*browser_entries_by_path_[path]);
        }
        
        for(std::string f: l.files) {
            //Create a Gtk::MenuItem and attach it to the parent
        }
        break;
    } 
    
    append(*browser_entries_by_path_[browser_root_]);
}
