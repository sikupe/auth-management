//
// Created by simon on 31.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTSTATUS_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTSTATUS_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(PermissionRequestStatus, v_int32,
     VALUE(Open, 1),
     VALUE(Granted, 2),
     VALUE(Declined, 3)

)

#include OATPP_CODEGEN_BEGIN(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTSTATUS_H
