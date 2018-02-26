#include "Interface/Router.h"
#include "Interface/Resource/Factory/Factory.h"

using namespace nghttp2::asio_http2::server;
using namespace Interface;
using namespace std;


Router::Router(http2 &server, string &docRoot)
   :serverM(server),
    docRootM(docRoot)
{
   init();
}

void Router::init()
{
   addRoute("/", "IndexResource");
   addRoute("/FileServer/", "FileServerResource");
   addRoute("/Statistics/", "StatisticsResource");
   addRoute("/RestApi/1.0/Measure/", "MeasureResource");
}

shared_ptr<Resource::AbstractResource> Router::createRequestHandler(const string & factory)
{
   shared_ptr<Resource::Factory::AbstractFactory> fac =
      Resource::Factory::Factory::createResourceFactory(factory);

   return fac->createResource(docRootM, exchangeM);
}

void Router::addRoute(const string & route, const string & factory)
{
   serverM.handle(route, [this, factory] (const request &req, const response &res)
   {
      createRequestHandler(factory)->handleRequest(req, res);
   });
}
