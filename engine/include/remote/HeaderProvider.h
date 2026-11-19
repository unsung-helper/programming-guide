#pragma once

#include <functional>
#include <string>
#include <unordered_map>

namespace us {

using HeaderProvider = std::function<std::unordered_map<std::string, std::string>()>;

}
