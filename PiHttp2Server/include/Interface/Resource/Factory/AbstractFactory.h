#ifndef _ABSTRACTFACTORY_H_
#define _ABSTRACTFACTORY_H_


#include <memory>
#include "Interface/Resource/AbstractResource.h"

namespace Interface {
namespace Resource {
namespace Factory {


    class AbstractFactory
    {
    public:
        virtual std::unique_ptr<Interface::Resource::AbstractResource> createResource(std::string & docRoot) = 0;

    };

} } }

#endif