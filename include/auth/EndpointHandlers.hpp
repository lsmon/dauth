#ifndef __ENDPOINT_HANDLERS_HPP__
#define __ENDPOINT_HANDLERS_HPP__

#include "http/Handler.hpp"

class Endpoint {
public:
    static void generateRsaKeys(const HttpRequest& request, HttpResponse& response, Path* path);

    static void handleAuthentication(const HttpRequest& request, HttpResponse& response, Path* path);

    static void retrieveRsaKeys(const HttpRequest& request, HttpResponse& response, Path* path);
};

#endif //__ENDPOINT_HANDLERS_HPP__