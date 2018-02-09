#ifndef _NOROUTERESOURCEFACTORY_H_
#define _NOROUTERESOURCEFACTORY_H_

#include "Interface/Resource/Factory/AbstractFactory.h"

namespace Interface {
namespace Resource {
namespace Factory {

    class NoRouteResourceFactory : public AbstractFactory
    {
    public:
        std::unique_ptr<Interface::Resource::AbstractResource> createResource(std::string & docRoot);
    };

} } }

#endif