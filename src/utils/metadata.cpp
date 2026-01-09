#include "utils/metadata.hpp"

namespace crotale::utils
{
    std::ostream& operator<<(std::ostream& os, const Version& version)
    {
        return os << (int) version.version_major << '.' << (int) version.version_minor << '.' << (int) version.version_patch;
    }

    Metadata::Metadata(std::string_view name, Version version, std::string_view license) :
        System(this), name(name), version(version), license(license) { }
}