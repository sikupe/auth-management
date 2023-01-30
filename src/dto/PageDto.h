//
// Created by simon on 28.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_PAGEDTO_H
#define AUTHORIZATION_MANAGEMENT_PAGEDTO_H

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<typename T>
class PageDto : public oatpp::DTO {
    DTO_INIT(PageDto, DTO);

    DTO_FIELD(Vector < T >, items);

    DTO_FIELD(UInt32 , size);
};

#include OATPP_CODEGEN_BEGIN(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PAGEDTO_H
