#include "sandbox.h"

int main(int argc, char **argv) {
    sandbox::Sandbox app({.name = "Transform CLI", .commandLineArgs = {.count = argc, .args = argv}});
    app.run();
}
