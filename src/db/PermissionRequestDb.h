//
// Created by simon on 07.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDB_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDB_H

#include "dto/PermissionRequest.h"
#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class PermissionRequestDb : public oatpp::orm::DbClient {
public:
    explicit PermissionRequestDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
            : oatpp::orm::DbClient(executor) {
    }

    QUERY(createPermissionRequest,
          "INSERT INTO permission_providers (type) VALUES (:pp.type) RETURNING *;",
          PREPARE(true),
          PARAM(oatpp::Object<PermissionRequest>, pp)
    )

    QUERY(deletePermissionRequest,
          "INSERT INTO permission_providers (type) VALUES (:id);",
          PREPARE(true),
          PARAM(oatpp::String, id)
    )

    QUERY(updatePermissionRequest,
          "UPDATE permission_providers SET type = :pp.type WHERE id=:pp.id RETURNING *;",
          PREPARE(true),
          PARAM(oatpp::Object<PermissionRequest>, pp)
    )

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDB_H
