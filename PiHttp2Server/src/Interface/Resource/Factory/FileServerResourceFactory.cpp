#include "Interface/Resource/Factory/FileServerResourceFactory.h"
#include "Interface/Resource/FileServerResource.h"

using namespace Interface::Resource;

std::unique_ptr<AbstractResource> Factory::FileServerResourceFactory::createResource(std::string & docRoot)
{
   return std::unique_ptr<AbstractResource>(new FileServerResource(docRoot));
}
