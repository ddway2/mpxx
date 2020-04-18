#include <stdlib.h>

#if defined(MPXX_HAVE_DEMANGLER)
#include <cxxabi.h>
#endif

#include <mpxx/utils.hpp>

namespace mpxx {

std::string
demangle_type_name(const std::string& mangled)
{
#if defined(MPXX_HAVE_DEMANGLER)
    char* buffer;
    int status;

    buffer = abi::__cxa_demangle(mangled.c_str(), 0, 0, &status);

    if (status == 0) {
        std::string n(buffer);
        free(buffer);

        return n;
    } else {
        return std::string("demangle failure");
    }

    return std::string("unsupported");
#else
    return mangled;
#endif
}

} // namespace mpxx
