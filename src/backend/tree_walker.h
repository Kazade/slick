#ifndef TREE_WALKER_H
#define TREE_WALKER_H

#include <vector>
#include <string>

class TreeWalker {
public:
    typedef std::vector<std::string> PathList;
    typedef std::vector<std::string> ExtList;

    TreeWalker(const std::string& root_dir);
    PathList find_files(const ExtList& extensions=ExtList());
    
private:
    std::vector<std::string> get_directories(const std::string& path);
    std::vector<std::string> get_files(const std::string& path);

    void recurse(const std::string& path, PathList& out);

    std::string root_;
};

#endif
