//
// Created by simon on 07.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERRESPONSE_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERRESPONSE_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "PermissionProviderType.h"
#include "dto/ConfigPairRequest.h"
#include "dto/PermissionProvider.h"


#include OATPP_CODEGEN_BEGIN(DTO)

class PermissionProviderResponse : public oatpp::DTO {
    DTO_INIT(PermissionProviderResponse, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(Enum < PermissionProviderType >, type, "type");

    DTO_FIELD(oatpp::Vector<oatpp::Object<ConfigPairRequest>>, config, "config");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERRESPONSE_H
