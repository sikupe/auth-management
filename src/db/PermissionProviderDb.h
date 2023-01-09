//
// Created by simon on 05.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERDB_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERDB_H


#include "dto/PermissionProvider.h"
#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class PermissionProviderDb : oatpp::orm::DbClient {
public:
    explicit PermissionProviderDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
            : oatpp::orm::DbClient(executor) {
    }

    QUERY(createPermissionProvider,
          "INSERT INTO permission_providers (type) VALUES (:pp.type) RETURNING *;",
          PREPARE(true),
          PARAM(oatpp::Object<PermissionProvider>, pp)
    )

    QUERY(deletePermissionProvider,
          "INSERT INTO permission_providers (type) VALUES (:id);",
          PREPARE(true),
          PARAM(oatpp::String, id)
    )

    QUERY(updatePermissionProvider,
          "UPDATE permission_providers SET type = :pp.type WHERE id=:pp.id RETURNING *;",
          PREPARE(true),
          PARAM(oatpp::Object<PermissionProvider>, pp)
    )
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERDB_H
