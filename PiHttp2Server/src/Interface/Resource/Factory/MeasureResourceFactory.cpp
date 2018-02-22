#include "Interface/Resource/MeasureResource.h"
#include "Interface/Resource/Factory/MeasureResourceFactory.h"

using namespace Interface::Resource;

std::unique_ptr<AbstractResource> Factory::MeasureResourceFactory::createResource(std::string & docRoot, Exchange::Exchange & exchange)
{
   return std::unique_ptr<AbstractResource>(new MeasureResource(docRoot, exchange));
}
