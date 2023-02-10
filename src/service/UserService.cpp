//
// Created by simon on 28.12.22.
//

#include "UserService.h"

oatpp::Object<UserDto> UserService::createUser(const oatpp::Object<UserDto> &dto) {
    auto dbResult = m_database->createUser(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getUserById(dto->id);
}

oatpp::Object<UserDto> UserService::updateUser(const oatpp::Object<UserDto> &dto) {
    auto dbResult = m_database->updateUser(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getUserById(dto->id);
}

oatpp::Object<UserDto> UserService::getUserById(const oatpp::String &id,
                                                const oatpp::provider::ResourceHandle<oatpp::orm::Connection> &connection) {
    auto dbResult = m_database->getUserById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    const auto r = result[0];

    return r;
}

oatpp::Object<PageDto<oatpp::Object<UserDto>>> UserService::getUsers() {
    auto dbResult = m_database->getAllUsers((unsigned int) 0, UINT32_MAX);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
//    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");


    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
    OATPP_LOGD("UserDb", "Item count=%d.", items->size());

    auto result = PageDto<oatpp::Object<UserDto>>::createShared();

    result->items = items;
    result->size = result->items->size();

    return result;
}


