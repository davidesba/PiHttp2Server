#ifndef _NOROUTERESOURCE_H_
#define _NOROUTERESOURCE_H_

#include "Interface/Resource/AbstractResource.h"

namespace Interface {
namespace Resource {


    class NoRouteResource : public AbstractResource
    {
    public:
      NoRouteResource(std::string & docRoot);
      ~NoRouteResource();
      virtual void handleRequest(const nghttp2::asio_http2::server::request & req,
                                 const nghttp2::asio_http2::server::response & res);
    };

} }

#endif