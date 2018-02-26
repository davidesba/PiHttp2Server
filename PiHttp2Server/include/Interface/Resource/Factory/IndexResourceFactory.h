#ifndef _INDEXRESOURCEFACTORY_H_
#define _INDEXRESOURCEFACTORY_H_

#include "Interface/Resource/Factory/AbstractFactory.h"

namespace Interface {
namespace Resource {
namespace Factory {

    class IndexResourceFactory : public AbstractFactory
    {
    public:
        std::unique_ptr<Interface::Resource::AbstractResource> createResource(
                  std::string & docRoot, Exchange::Exchange & exchange);
    };

} } }

#endif