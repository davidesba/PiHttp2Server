#include "Interface/Resource/Factory/IndexResourceFactory.h"
#include "Interface/Resource/IndexResource.h"

using namespace Interface::Resource;

std::unique_ptr<AbstractResource> Factory::IndexResourceFactory::createResource(std::string & docRoot, Exchange::Exchange & exchange)
{
   return std::unique_ptr<AbstractResource>(new IndexResource(docRoot, exchange));
}
