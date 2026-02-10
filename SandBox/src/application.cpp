#include "application.h"

namespace app {

    Application::Application(const ApplicationSpecification &specification)
        : m_specification(specification), m_app(specification.name) {}

    void Application::run() {
        const ApplicationCommandLineArgs &args = m_specification.commandLineArgs;
        try {
            m_app.parse(args.count, args.args);
        } catch (const CLI::ParseError &e) {
            m_app.exit(e);
        }
    }
} // namespace app