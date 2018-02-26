#ifndef _STATISTICSRESOURCEFACTORY_H_
#define _STATISTICSRESOURCEFACTORY_H_

#include "Interface/Resource/Factory/AbstractFactory.h"

namespace Interface {
namespace Resource {
namespace Factory {

    class StatisticsResourceFactory : public AbstractFactory
    {
    public:
        std::unique_ptr<Interface::Resource::AbstractResource> createResource(
                  std::string & docRoot, Exchange::Exchange & exchange);
    };

} } }

#endif