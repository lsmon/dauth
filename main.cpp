#include <csignal>
#include "auth/DServer.hpp"

int main(int argc, char** argv) {
    std::shared_ptr<ApiAuthDServer> api = std::make_unique<ApiAuthDServer>();
    api->init();
    return EXIT_SUCCESS;
}