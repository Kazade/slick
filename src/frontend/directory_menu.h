#ifndef DIRECTORY_MENU_H
#define DIRECTORY_MENU_H

#include <gtkmm.h>
#include <string>
#include "kazbase/logging/logging.h"

typedef sigc::signal<void, std::string> SignalFileClicked;
typedef sigc::signal<void> SignalChangeDirectoryClicked;

class DirectoryMenu : public Gtk::MenuItem {
public:
    DirectoryMenu(const std::string& path, bool is_root=true);

    bool build(Cairo::RefPtr<Cairo::Context> context);

    SignalFileClicked& signal_file_clicked() { return signal_file_clicked_; }
    SignalChangeDirectoryClicked& signal_change_directory_clicked() { return signal_change_directory_clicked_; }

    void on_file_item_clicked(const std::string& file_path) {
        L_DEBUG("on_file_item_clicked: " + file_path);
        signal_file_clicked_(file_path);
    }

    void on_change_directory_clicked() {
        L_DEBUG("Change directory clicked");
        signal_change_directory_clicked_();
    }

private:
    std::string path_;
    bool built_;
    bool is_root_;

    SignalFileClicked signal_file_clicked_;
    SignalChangeDirectoryClicked signal_change_directory_clicked_;
};

#endif
