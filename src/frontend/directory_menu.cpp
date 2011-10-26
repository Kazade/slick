#include "directory_menu.h"

#include "kazbase/logging/logging.h"
#include "kazbase/os/path.h"
#include "kazbase/string.h"

#include <glib/gi18n.h>

DirectoryMenu::DirectoryMenu(const std::string& path, bool is_root):
    Gtk::MenuItem(os::path::split(path).second),
    path_(path),
    built_(false),
    is_root_(is_root) {
    
    L_DEBUG("DirectoryMenu::DirectoryMenu() called with path: " + path);
    
    set_submenu(*Gtk::manage(new Gtk::Menu()));
    
    //Build on the first draw
    signal_draw().connect(sigc::mem_fun(*this, &DirectoryMenu::build));
}

bool DirectoryMenu::build(Cairo::RefPtr<Cairo::Context> context) {
    if(built_) return false;
    
    L_DEBUG("Building directory menu");
   
    if(is_root_) {
        //If this is the root of the tree, add the change directory entry
        //first
        Gtk::MenuItem* cd = Gtk::manage(new Gtk::MenuItem(_("Change directory...")));
        get_submenu()->append(*cd);
        get_submenu()->append(*Gtk::manage(new Gtk::SeparatorMenuItem()));
    }
        
    bool item_added = false;
    
    //Go through the current directory recursively add sub menus
    std::vector<std::string> dirs = os::path::list_dir(path_);
    std::sort(dirs.begin(), dirs.end());
    for(std::string d: dirs) {
        std::string path = os::path::join(path_, d);

        if(!os::path::is_dir(path)) continue;        
        if(str::starts_with(d, ".")) continue;
        
        DirectoryMenu* new_menu = Gtk::manage(new DirectoryMenu(path, false));
        get_submenu()->append(*new_menu);
        
        item_added = true;
    }
    
    //Now go through the files in the directory, and add them as
    //menu items    
    for(std::string f: os::path::list_dir(path_)) {
        std::string path = os::path::join(path_, f);

        if(!os::path::is_file(path)) continue;        
        if(str::starts_with(f, ".")) continue;
        if(str::ends_with(f, "~")) continue;
            
        Gtk::MenuItem* new_item = Gtk::manage(new Gtk::MenuItem(f));
        get_submenu()->append(*new_item);
        
        item_added = true;
    }

    if(!item_added) {
        Gtk::MenuItem* empty_item = Gtk::manage(new Gtk::MenuItem("Empty directory"));
        empty_item->set_sensitive(false);
        get_submenu()->append(*empty_item);
    }
 
    L_DEBUG("Build complete");
    get_submenu()->show_all();
       
    built_ = true;    
    return false;
}

