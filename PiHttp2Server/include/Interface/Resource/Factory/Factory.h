#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <string>
#include <memory>
#include "Interface/Resource/Factory/AbstractFactory.h"

namespace Interface {
namespace Resource {
namespace Factory {


    class Factory
    {
    public:
        static std::unique_ptr<AbstractFactory> createResourceFactory(const std::string &index);

    private:
        Factory();
    };


} } }

#endif