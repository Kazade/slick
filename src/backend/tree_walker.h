#ifndef TREE_WALKER_H
#define TREE_WALKER_H

#include <vector>
#include <string>

class TreeWalker {
public:
    typedef std::vector<std::string> PathList;
    typedef std::vector<std::string> ExtList;

    struct Level {
        std::string root;
        std::vector<std::string> dirs;
        std::vector<std::string> files;
    };

    TreeWalker(const std::string& root_dir);
    PathList find_files(const ExtList& extensions=ExtList());
    
    std::vector<TreeWalker::Level> walk() const;
    
private:
    std::vector<std::string> get_directories(const std::string& path) const;
    std::vector<std::string> get_files(const std::string& path) const;

    void recurse(const std::string& path, PathList& out) const;

    void walker(const std::string& path, std::vector<TreeWalker::Level>& result) const;
    
    std::string root_;
};

#endif
