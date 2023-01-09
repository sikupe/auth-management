//
// Created by simon on 02.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERTYPE_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERTYPE_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(PermissionProviderType, v_int32,
     VALUE(KeyCloak, 1)
)

#include OATPP_CODEGEN_BEGIN(DTO)


#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERTYPE_H
