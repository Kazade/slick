#include <gtkmm.h>

#include "kazbase/os/path.h"
#include "kazbase/logging/logging.h"
#include "kazbase/fdo/base_directory.h"

#include "frontend/main_window.h"

#define PROGRAM_NAME_LOWER "slick"

int main(int argc, char* argv[]) {
    std::string cache_home = fdo::xdg::get_or_create_program_cache_path(PROGRAM_NAME_LOWER);
    std::string log = os::path::join(cache_home, "debug.log");
    logging::get_logger("/")->add_handler(logging::Handler::ptr(new logging::StdIOHandler));
    logging::get_logger("/")->add_handler(logging::Handler::ptr(new logging::FileHandler(log)));
    
    Gtk::Main kit(argc, argv);
    
    MainWindow window;
    
    Gtk::Main::run();
        
    return 0;
}
