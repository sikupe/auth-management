//
// Created by simon on 28.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_CONFIGDTO_H
#define AUTHORIZATION_MANAGEMENT_CONFIGDTO_H

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigDto : public oatpp::DTO {

    DTO_INIT(ConfigDto, DTO)

    DTO_FIELD(String, dbConnectionString);

};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_CONFIGDTO_H
