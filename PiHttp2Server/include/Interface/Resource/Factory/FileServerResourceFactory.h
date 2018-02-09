#ifndef _FILESERVERRESOURCEFACTORY_H_
#define _FILESERVERRESOURCEFACTORY_H_

#include "Interface/Resource/Factory/AbstractFactory.h"

namespace Interface {
namespace Resource {
namespace Factory {

    class FileServerResourceFactory : public AbstractFactory
    {
    public:
        std::unique_ptr<Interface::Resource::AbstractResource> createResource(std::string & docRoot);
    };

} } }

#endif