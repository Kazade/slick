#include "tree_walker.h"

#include "kazbase/os/path.h"

TreeWalker::TreeWalker(const std::string& root_dir):
    root_(root_dir) {

}

TreeWalker::PathList TreeWalker::find_files(const ExtList& extensions) {
    PathList result;
    recurse(root_, result);
    
    PathList stripped;
    for(std::string s: result) {
        if(os::path::is_file(s)) {
            //FIXME: Check extension
            stripped.push_back(s);
        }
    }
    
    //TODO: Sort
    return stripped;
}

TreeWalker::PathList TreeWalker::get_directories(const std::string& path) {
    PathList result;
    
    for(std::string f: os::path::list_dir(path)) {
        std::string f_path = os::path::join(path, f);
        if(os::path::is_dir(f)) {
            result.push_back(f_path);
        }
    }
    return result;
}

TreeWalker::PathList TreeWalker::get_files(const std::string& path) {
    PathList result;
    
    for(std::string f: os::path::list_dir(path)) {
        std::string f_path = os::path::join(path, f);
        if(os::path::is_file(f)) {
            result.push_back(f_path);
        }
    }
    
    return result;
}

void TreeWalker::recurse(const std::string& path, PathList& out) {
    //Recurse into directories
    for(std::string d: get_directories(path)) {
        recurse(d, out);
    }
    
    //Just store files
    for(std::string f: get_files(path)) {
        out.push_back(f);
    }
}
