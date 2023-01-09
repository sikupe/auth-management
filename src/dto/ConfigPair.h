//
// Created by simon on 02.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_CONFIGPAIR_H
#define AUTHORIZATION_MANAGEMENT_CONFIGPAIR_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigPair : public oatpp::DTO {
    DTO_INIT(ConfigPair, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(String, key, "key");

    DTO_FIELD(String, value, "value");
};

#include OATPP_CODEGEN_END(DTO)


#endif //AUTHORIZATION_MANAGEMENT_CONFIGPAIR_H
