//
// Created by simon on 07.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_CONFIGPAIRREQUEST_H
#define AUTHORIZATION_MANAGEMENT_CONFIGPAIRREQUEST_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigPairRequest : public oatpp::DTO {
    DTO_INIT(ConfigPairRequest, DTO);

    DTO_FIELD(String, key, "key");

    DTO_FIELD(String, value, "value");
};

#include OATPP_CODEGEN_END(DTO)


#endif //AUTHORIZATION_MANAGEMENT_CONFIGPAIRREQUEST_H
