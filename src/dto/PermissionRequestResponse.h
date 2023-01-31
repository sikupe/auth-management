//
// Created by simon on 30.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTRESPONSE_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTRESPONSE_H


#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "PermissionResponse.h"


#include OATPP_CODEGEN_BEGIN(DTO)
#include "PermissionRequestStatus.h"

class PermissionRequestResponse : public oatpp::DTO {
    DTO_INIT(PermissionRequestResponse, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(String, requestor, "requester");

    DTO_FIELD(UInt64, request_date, "request_date");

    DTO_FIELD(UInt64, invalidation_date, "invalidation_date");

    DTO_FIELD(Enum<PermissionRequestStatus>, status, "status");

    DTO_FIELD(oatpp::Object<PermissionResponse>, permission, "permission");
};

#include OATPP_CODEGEN_END(DTO)


#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTRESPONSE_H
