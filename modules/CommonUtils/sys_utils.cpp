#include "sys_utils.h"


#include <fstream>
#include <filesystem>
#include "logger.h"


#include <random>

#if defined(HAVE_X11)
#include <X11/Xlib.h>
#endif

namespace wl {

    std::string getDefaultFolder() {
        return "./tmp";
    }

    std::string getCurrFilePath() {
        return std::filesystem::current_path().string();
    }
}
