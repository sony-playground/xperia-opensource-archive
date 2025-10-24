#ifndef FL_EXCEPTION_H_
#define FL_EXCEPTION_H_

#include <string>
#include <vector>

#define THROW_FL_EXCEPTION(s)   throw FLException(__FILE__, __LINE__, s)

template <typename ... T>
std::string str_format(const std::string& format, T ... args) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
    size_t length = std::snprintf(nullptr, 0, format.c_str(), args ...);
#pragma GCC diagnostic pop
    std::vector<char> buffer(length + 1);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
    std::snprintf(&buffer[0], length + 1, format.c_str(), args ...);
#pragma GCC diagnostic pop
    return std::string(&buffer[0], &buffer[0] + length);
}

class FLException {
    private:
        const std::string mesg;

    public:
        FLException(const std::string file, const int line, const std::string desc):
            mesg(str_format("%s [%s:%d]", desc.c_str(), file.c_str(), line)) {}
        inline const char* what(void) const {
            return mesg.c_str();
        }
};

#endif  // FL_EXCEPTION_H_
