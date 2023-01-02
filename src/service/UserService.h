//
// Created by simon on 28.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_USERSERVICE_H
#define AUTHORIZATION_MANAGEMENT_USERSERVICE_H

#include <oatpp/orm/Connection.hpp>
#include <oatpp/core/provider/Provider.hpp>
#include <oatpp/web/protocol/http/Http.hpp>
#include "db/UserDb.h"

#include "oatpp/core/macro/component.hpp"
#include "dto/UserDto.h"
#include "db/UserDb.h"
#include "dto/PageDto.h"

class UserService {
private:
    typedef oatpp::web::protocol::http::Status Status;
private:
    OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
public:

    oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto> &dto);

    oatpp::Object<UserDto> updateUser(const oatpp::Object<UserDto> &dto);

    oatpp::Object<UserDto> getUserById(const oatpp::String &id,
                                       const oatpp::provider::ResourceHandle<oatpp::orm::Connection> &connection = nullptr);

    oatpp::Object<PageDto<oatpp::Object<UserDto>>> getUsers();

};


#endif //AUTHORIZATION_MANAGEMENT_USERSERVICE_H
