#pragma once

#include <CLI/CLI.hpp>

#include <any>
#include <string>
#include <vector>
#include <optional>
#include <tuple>
#include <utility>

#include "command.h"


namespace app {

    struct ApplicationCommandLineArgs {
        int count = 0;
        char** args = nullptr;

        const char* operator[](int index) const { return args[index]; }
    };

    struct ApplicationSpecification {
        std::string name;
        ApplicationCommandLineArgs commandLineArgs;
    };

    class Application {
    public:
        explicit Application(const ApplicationSpecification& specification);
        virtual ~Application() = default;

        void run();

        template <typename... Args>
        void pushCommand(const Command<Args...>& command);

    private:
        ApplicationSpecification m_specification;
        CLI::App m_app;
        std::vector<std::any> m_commandArgsStore;

        template <typename T>
        struct is_std_optional : std::false_type {};

        template <typename T>
        struct is_std_optional<std::optional<T>> : std::true_type {};

        template <typename T>
        static inline constexpr bool is_std_optional_v = is_std_optional<T>::value;
    };

    template <typename... Args>
    void Application::pushCommand(const Command<Args...>& command) {

        auto* appCommand = m_app.add_subcommand(std::string(command.specification.name), std::string(command.specification.description));

        m_commandArgsStore.push_back(std::tuple<Args...>{});
        auto& args = std::any_cast<std::tuple<Args...> &>(m_commandArgsStore.back());

        const auto& argSpecifications = command.specification.argSpecifications;
        [&] <size_t... I>(std::index_sequence<I...>) {
            (([&]() {
                auto* option = appCommand->add_option(
                    std::string(std::get<I>(argSpecifications).name),
                    std::get<I>(args),
                    std::string(std::get<I>(argSpecifications).description)
                );
                if constexpr (!is_std_optional_v<std::tuple_element_t<I, std::tuple<Args...>>>) {
                    option->required();
                }
                }()), ...);
        }(std::make_index_sequence<sizeof...(Args)>{});

        appCommand->callback([command, &args]() {
            std::apply(command.callback, args);
            });
    }
}