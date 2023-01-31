//
// Created by simon on 30.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDTO_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDTO_H


#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "PermissionRequestStatus.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PermissionRequestDto : public oatpp::DTO {
    DTO_INIT(PermissionRequestDto, DTO);

    DTO_FIELD(String, requestor, "requester");

    DTO_FIELD(UInt32, invalidation_date, "invalidation_date");

    DTO_FIELD(String, permission_id, "permission_id");

    DTO_FIELD(Enum<PermissionRequestStatus>, status, "status");
};

#include OATPP_CODEGEN_END(DTO)


#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTDTO_H
