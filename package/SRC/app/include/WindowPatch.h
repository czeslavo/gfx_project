#include<sstream>

/**
 * Patch used for windows build, since gcc in mingw doesn't support this function.
 */
namespace std {
    template<typename T>
    std::string to_string(T value) {
        std::ostringstream os;
        os << value;
        return os.str();
    }
}