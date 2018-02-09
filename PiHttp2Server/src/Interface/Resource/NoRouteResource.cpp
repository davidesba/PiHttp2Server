#include "Interface/Resource/NoRouteResource.h"

using namespace Interface::Resource;
using namespace nghttp2::asio_http2::server;

NoRouteResource::NoRouteResource(std::string & docRoot)
   :AbstractResource(docRoot)
{}

NoRouteResource::~NoRouteResource() {}

void NoRouteResource::handleRequest(const request &req, const response &res)
{
   res.write_head(404);
   res.end();
}
