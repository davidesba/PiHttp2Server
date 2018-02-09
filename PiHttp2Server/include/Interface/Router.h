#include <map>
#include <string>
#include "Resource/Factory/AbstractFactory.h"
#include <nghttp2/asio_http2_server.h>

namespace Interface {

    class Router
    {
    public:
        Router(nghttp2::asio_http2::server::http2 &server, std::string& docRoot);
        void addRoute(const std::string & path, const std::string & factory);
        std::shared_ptr<Resource::AbstractResource> createRequestHandler(const std::string & factory);

    private:
        void init();
        nghttp2::asio_http2::server::http2 &serverM;
        std::string &docRootM;
    };
}
