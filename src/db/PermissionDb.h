//
// Created by simon on 05.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONDB_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONDB_H


#include "dto/Permission.h"
#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class PermissionDb : public oatpp::orm::DbClient {
public:
    explicit PermissionDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
            : oatpp::orm::DbClient(executor) {
    }

    QUERY(createPermission,
          "INSERT INTO permissions(permission_provider_id, name, description) "
          "VALUES(:permission.permission_provider_id, :permission.name, :permission.description) "
          "RETURNING *;",
          PREPARE(true),
          PARAM(oatpp::Object<Permission>, permission))

    QUERY(deletePermission,
          "DELETE FROM permissions WHERE id = :id;",
          PREPARE(true),
          PARAM(oatpp::String, id)
    )

    QUERY(updatePermission,
          "UPDATE permissions SET"
          " permission_provider_id = :permission.permission_provider_id, "
          " name = :permission.name, "
          " description = :permission.description "
          "WHERE"
          " id = :permission.permission_provider_id "
          "RETURNING *;",
          PREPARE(true),
          PARAM(oatpp::Object<Permission>, permission)
    )

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen


#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONDB_H
