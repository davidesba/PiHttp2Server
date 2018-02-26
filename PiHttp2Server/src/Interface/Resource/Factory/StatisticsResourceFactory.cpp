#include "Interface/Resource/Factory/StatisticsResourceFactory.h"
#include "Interface/Resource/StatisticsResource.h"

using namespace Interface::Resource;

std::unique_ptr<AbstractResource> Factory::StatisticsResourceFactory::createResource(std::string & docRoot, Exchange::Exchange & exchange)
{
   return std::unique_ptr<AbstractResource>(new StatisticsResource(docRoot, exchange));
}
