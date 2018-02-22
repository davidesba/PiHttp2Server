#include "Interface/Resource/NoRouteResource.h"
#include "Interface/Resource/Factory/NoRouteResourceFactory.h"

using namespace Interface::Resource;

std::unique_ptr<AbstractResource> Factory::NoRouteResourceFactory::createResource(std::string & docRoot, Exchange::Exchange & exchange)
{
   return std::unique_ptr<AbstractResource>(new NoRouteResource(docRoot, exchange));
}
