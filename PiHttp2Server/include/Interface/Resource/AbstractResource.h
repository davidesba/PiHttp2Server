#ifndef _ABSTRACTRESOURCE_H_
#define _ABSTRACTRESOURCE_H_

#include <nghttp2/asio_http2_server.h>

namespace Interface {
namespace Resource {


    class AbstractResource
    {
    public:
        AbstractResource(std::string & docRoot);
        virtual ~AbstractResource();

        virtual void handleRequest(const nghttp2::asio_http2::server::request & req,
                                   const nghttp2::asio_http2::server::response & res);

    protected:
        std::string &docRootM;

        virtual void handle_get(const nghttp2::asio_http2::server::request & req,
                                const nghttp2::asio_http2::server::response & res);
        virtual void handle_put(const nghttp2::asio_http2::server::request &req,
                                const nghttp2::asio_http2::server::response &res);
        virtual void handle_post(const nghttp2::asio_http2::server::request &req,
                                 const nghttp2::asio_http2::server::response &res);
        virtual void handle_delete(const nghttp2::asio_http2::server::request &req,
                                   const nghttp2::asio_http2::server::response &res);
    };

} }

#endif