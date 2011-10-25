#include "tree_walker.h"

#include "kazbase/logging/logging.h"
#include "kazbase/os/path.h"
#include "kazbase/string.h"

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

TreeWalker::PathList TreeWalker::get_directories(const std::string& path) const {
    PathList result;
    
    for(std::string f: os::path::list_dir(path)) {
        if(str::starts_with(f, ".")) continue;
        
        std::string f_path = os::path::join(path, f);
        if(os::path::is_dir(f_path)) {
            result.push_back(f);
        } else {
            L_DEBUG("Is not a directory: " + f_path);
        }
    }
    return result;
}

TreeWalker::PathList TreeWalker::get_files(const std::string& path) const {
    PathList result;
    
    for(std::string f: os::path::list_dir(path)) {
        std::string f_path = os::path::join(path, f);
        if(os::path::is_file(f)) {
            result.push_back(f);
        }
    }
    
    return result;
}

void TreeWalker::recurse(const std::string& path, PathList& out) const {
    //Recurse into directories
    for(std::string d: get_directories(path)) {
        recurse(d, out);
    }
    
    //Just store files
    for(std::string f: get_files(path)) {
        out.push_back(f);
    }
}

void TreeWalker::walker(const std::string& path, std::vector<TreeWalker::Level>& result) const {
    TreeWalker::Level new_result;
    new_result.dirs = get_directories(path);
    new_result.files = get_files(path);
    new_result.root = path;
    
    L_DEBUG(path);
    
    result.push_back(new_result);
    
    for(std::string d: new_result.dirs) {
        walker(os::path::join(path, d), result);
    }
}

std::vector<TreeWalker::Level> TreeWalker::walk() const {
    std::vector<TreeWalker::Level> result;

    walker(root_, result);
    
    return result;
}

    
    
