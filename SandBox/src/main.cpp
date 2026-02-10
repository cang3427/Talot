#include "application.h"

#include <iostream>

int main(int argc, char **argv) {
    app::Application app({.name = "Transform CLI",
                        .commandLineArgs = {.count = argc, .args = argv}});
    app.run();
}
