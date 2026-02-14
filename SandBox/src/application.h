#pragma once

#include <CLI/CLI.hpp>

#include <any>
#include <string>
#include <deque>
#include <optional>
#include <tuple>
#include <utility>
#include <concepts>

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

        virtual void run();

        template <typename Callback, typename... Args>
            requires std::invocable<Callback, Args...>
        void pushCommand(const CommandSpecification<Args...>& specification, Callback callback);

    private:
        ApplicationSpecification m_specification;
        CLI::App m_app;
        std::deque<std::any> m_commandArgsStore;

        template<typename T>
        struct is_std_array : std::false_type {};

        template<typename T, std::size_t N>
        struct is_std_array<std::array<T, N>> : std::true_type {};

        template<typename T>
        static inline constexpr bool is_std_array_v = is_std_array<T>::value;
    };

    template <typename Callback, typename... Args>
        requires std::invocable<Callback, Args...>
    void Application::pushCommand(const CommandSpecification<Args...>& commandSpecification, Callback callback) {

        auto* appCommand = m_app.add_subcommand(
            std::string(commandSpecification.name),
            std::string(commandSpecification.description)
        );

        const auto& argSpecifications = commandSpecification.argSpecifications;

        m_commandArgsStore.push_back([&]() {
            std::tuple<Args...> t;
            [&] <std::size_t... I>(std::index_sequence<I...>) {
                t = std::tuple{ std::get<I>(argSpecifications).defaultValue... };
            }(std::make_index_sequence<sizeof...(Args)>{});
            return t;
            }());

        auto& args = std::any_cast<std::tuple<Args...>&>(m_commandArgsStore.back());

        [&] <size_t... I>(std::index_sequence<I...>) {
            (([&]() {
                const auto& argSpecification = std::get<I>(argSpecifications);
                auto& arg = std::get<I>(args);

                auto* option = appCommand->add_option(
                    std::string(argSpecification.name),
                    arg,
                    std::string(argSpecification.description)
                );

                if (argSpecification.required) {
                    option->required();
                }

                if constexpr (is_std_array_v<std::tuple_element_t<I, std::tuple<Args...>>>) {
                    option->expected(
                        std::tuple_size_v<std::tuple_element_t<I, std::tuple<Args...>>>
                    );
                }

                }()), ...);
        }(std::make_index_sequence<sizeof...(Args)>{});

        appCommand->callback([callback, &args]() {
            std::apply(callback, args);
            });
    }
}
