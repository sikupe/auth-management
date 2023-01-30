//
// Created by simon on 30.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_CONFIGCOMPONENT_H
#define AUTHORIZATION_MANAGEMENT_CONFIGCOMPONENT_H

#include "dto/ConfigDto.h"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

#include "oatpp/core/base/CommandLineArguments.hpp"

#include <cstdlib>

class ConfigComponent {
public:

    /**
     * This should be configured through config-server ex. Consul
     */
    OATPP_CREATE_COMPONENT(ConfigDto, config)([] {
        const char *connectionString = std::getenv("DATABASE_CONNECTION"); // first read from env variable
        if (connectionString == nullptr) {
            throw std::runtime_error("Database connection config missing!");
        }

        ConfigDto configDto;
        configDto.dbConnectionString = connectionString;
        return configDto;
    }());
};

#endif //AUTHORIZATION_MANAGEMENT_CONFIGCOMPONENT_H
