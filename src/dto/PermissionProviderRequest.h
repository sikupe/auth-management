//
// Created by simon on 07.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERREQUEST_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERREQUEST_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "PermissionProviderType.h"
#include "dto/ConfigPairRequest.h"
#include "dto/PermissionProvider.h"


#include OATPP_CODEGEN_BEGIN(DTO)

class PermissionProviderRequest : public oatpp::DTO {
    DTO_INIT(PermissionProviderRequest, DTO);

    DTO_FIELD(Enum < PermissionProviderType >, type, "type");

    DTO_FIELD(oatpp::Vector<oatpp::Object<ConfigPairRequest>>, config, "config");

public:
    oatpp::Object<PermissionProvider> toPermissionProvider();
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERREQUEST_H
