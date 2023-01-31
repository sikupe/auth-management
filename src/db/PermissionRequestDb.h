//
// Created by simon on 07.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDB_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDB_H

#include "dto/PermissionRequest.h"
#include <oatpp-postgresql/orm.hpp>
#include <ctime>

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen
#include "dto/PermissionRequestDto.h"

class PermissionRequestDb : public oatpp::orm::DbClient {
public:
    explicit PermissionRequestDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
            : oatpp::orm::DbClient(executor) {
    }

    QUERY(createPermissionRequest,
          "INSERT INTO permission_requests (requester, request_date, invalidation_date, permission_id) VALUES (:pp.requester, :pp.invalidation_date, :requestedDate, :pp.permission_id) RETURNING *;",
          PREPARE(true),
          PARAM(oatpp::Object<PermissionRequestDto>, pp),
          PARAM(oatpp::UInt32, requestedDate)
    )

    QUERY(deletePermissionRequest,
          "DELETE FROM permission_requests WHERE id = :id;",
          PREPARE(true),
          PARAM(oatpp::String, id)
    )

    QUERY(updatePermissionRequest,
          "UPDATE permission_requests SET requester = :pp.requester, invalidation_date = :pp.invalidation_date, permission_id = :pp.permission_id, status = :pp.status WHERE id=:id RETURNING *;",
          PREPARE(true),
          PARAM(oatpp::String, id),
          PARAM(oatpp::Object<PermissionRequestDto>, pp)
    )

    QUERY(getPermissionRequest,
          "SELECT * FROM permission_requests WHERE id=:id;",
          PREPARE(true),
          PARAM(oatpp::String, id)
    )

    QUERY(listPermissionRequest,
          "SELECT * FROM permission_requests OFFSET :offset LIMIT :limit;",
          PREPARE(true),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit)
    )
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDB_H
