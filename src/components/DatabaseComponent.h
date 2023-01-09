//
// Created by simon on 09.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_DATABASECOMPONENT_H
#define AUTHORIZATION_MANAGEMENT_DATABASECOMPONENT_H

#include <oatpp/core/macro/component.hpp>
#include "db/UserDb.h"
#include "db/PermissionProviderDb.h"
#include "db/ConfigPairDb.h"
#include "db/PermissionDb.h"
#include "dto/ConfigDto.h"

class DatabaseComponent {
public:

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::postgresql::ConnectionProvider>,
                           dbConnectionProvider)([] {

        OATPP_COMPONENT(ConfigDto, config); // Get config component

        /* Create database-specific ConnectionProvider */
        auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(config.dbConnectionString);

        return connectionProvider;
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, userDb)([] {

        OATPP_COMPONENT(ConfigDto, config); // Get config component

        OATPP_COMPONENT(std::shared_ptr<oatpp::postgresql::ConnectionProvider>, connectionProvider);

        /* Create database-specific ConnectionPool */
        auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                              10 /* max-connections */,
                                                                              std::chrono::seconds(
                                                                                      5) /* connection TTL */);

        /* Create database-specific Executor */
        auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

        /* Create MyClient database client */
        return std::make_shared<UserDb>(executor);

    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<PermissionProviderDb>, permissionProviderDb)([] {

        OATPP_COMPONENT(ConfigDto, config); // Get config component

        OATPP_COMPONENT(std::shared_ptr<oatpp::postgresql::ConnectionProvider>, connectionProvider);

        /* Create database-specific ConnectionPool */
        auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                              10 /* max-connections */,
                                                                              std::chrono::seconds(
                                                                                      5) /* connection TTL */);

        /* Create database-specific Executor */
        auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

        /* Create MyClient database client */
        return std::make_shared<PermissionProviderDb>(executor);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<ConfigPairDb>, configPairDb)([] {

        OATPP_COMPONENT(ConfigDto, config); // Get config component

        OATPP_COMPONENT(std::shared_ptr<oatpp::postgresql::ConnectionProvider>, connectionProvider);

        /* Create database-specific ConnectionPool */
        auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                              10 /* max-connections */,
                                                                              std::chrono::seconds(
                                                                                      5) /* connection TTL */);

        /* Create database-specific Executor */
        auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

        /* Create MyClient database client */
        return std::make_shared<ConfigPairDb>(executor);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<PermissionDb>, permissionDb)([] {

        OATPP_COMPONENT(ConfigDto, config); // Get config component

        OATPP_COMPONENT(std::shared_ptr<oatpp::postgresql::ConnectionProvider>, connectionProvider);

        /* Create database-specific ConnectionPool */
        auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                              10 /* max-connections */,
                                                                              std::chrono::seconds(
                                                                                      5) /* connection TTL */);

        /* Create database-specific Executor */
        auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

        /* Create MyClient database client */
        return std::make_shared<PermissionDb>(executor);
    }());
};

#endif //AUTHORIZATION_MANAGEMENT_DATABASECOMPONENT_H
