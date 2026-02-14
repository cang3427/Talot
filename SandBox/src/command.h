#pragma once

#include <array>
#include <optional>
#include <string_view>
#include <tuple>
#include <concepts>

namespace app {

    template <typename T>
    struct CommandArgSpecification {
        std::string_view name;
        std::string_view description;
        T defaultValue{};
        bool required = false;
    };

    template <typename... Args> 
    struct CommandSpecification {
        std::string_view name;
        std::string_view description;
		std::tuple<CommandArgSpecification<Args>...> argSpecifications;
    };
} // namespace app