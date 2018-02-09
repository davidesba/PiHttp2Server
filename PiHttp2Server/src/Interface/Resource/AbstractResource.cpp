#include "Interface/Resource/AbstractResource.h"

using namespace Interface::Resource;
using namespace nghttp2::asio_http2::server;

AbstractResource::AbstractResource(std::string & docRoot)
   :docRootM(docRoot)
{}

AbstractResource::~AbstractResource()
{}

void AbstractResource::handleRequest(const request & req, const response & res)
{
   if (req.method() == "GET")
   {
      handle_get(req, res);
   }
   else if (req.method() == "PUT")
   {
      handle_put(req, res);
   }
   else if (req.method() == "POST")
   {
      handle_post(req, res);
   }
   else if (req.method() == "DELETE")
   {
      handle_delete(req, res);
   }
   else
   {
      res.write_head(405);
      res.end();
   }
}

void AbstractResource::handle_get(const request & req, const response & res)
{
   res.write_head(405);
   res.end();
}

void AbstractResource::handle_put(const request &req, const response &res)
{
   res.write_head(405);
   res.end();
}

void AbstractResource::handle_post(const request &req, const response &res)
{
   res.write_head(405);
   res.end();
}

void AbstractResource::handle_delete(const request &req, const response &res)
{
   res.write_head(405);
   res.end();
}
