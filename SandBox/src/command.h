#pragma once
#include <array>
#include <optional>
#include <string_view>
#include <tuple>


namespace app {

    template <typename T>
    struct CommandArgSpecification {
        std::string_view name;
        std::string_view description;
    };

    template <typename... Args> 
    struct CommandSpecification {
        std::string_view name;
        std::string_view description;
		std::tuple<CommandArgSpecification<Args>...> argSpecifications;
    };

    template <typename... Args>
    struct Command {
        CommandSpecification<Args...> specification;
        std::function<void(Args...)> callback;
    };
} // namespace app