//
// Created by simon on 02.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUEST_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUEST_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "PermissionRequestStatus.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PermissionRequest : public oatpp::DTO {
    DTO_INIT(PermissionRequest, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(String, requestor, "requester");

    DTO_FIELD(UInt64, request_date, "request_date");

    DTO_FIELD(UInt64, invalidation_date, "invalidation_date");

    DTO_FIELD(String, permission_id, "permission_id");

    DTO_FIELD(Enum<PermissionRequestStatus>, status, "status");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUEST_H
