//
// Created by simon on 09.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_USERDB_H
#define AUTHORIZATION_MANAGEMENT_USERDB_H

#include "dto/UserDto.h"
#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class UserDb : public oatpp::orm::DbClient {
public:
    explicit UserDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
            : oatpp::orm::DbClient(executor) {

        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
        migration.addFile(2, DATABASE_MIGRATIONS "/002_example_data.sql");
        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("UserDb", "Migration - OK. Version=%d.", version);
    }

    QUERY(createUser,
          "INSERT INTO users"
          "(id, username, email, is_admin) VALUES "
          "(uuid_generate_v4(), :user.username, :user.email, :user.is_admin)"
          "RETURNING *;",
          PREPARE(true), // user prepared statement!
          PARAM(oatpp::Object<UserDto>, user)
    )

    QUERY(updateUser,
          "UPDATE users "
          "SET "
          " username=:user.username, "
          " email=:user.email, "
          " is_admin=:user.is_admin "
          "WHERE "
          " id=:user.id "
          "RETURNING *;",
          PREPARE(true), //<-- user prepared statement!
          PARAM(oatpp::Object<UserDto>, user)
    )

    QUERY(getUserById,
          "SELECT * FROM users WHERE id=:id;",
          PREPARE(true), //<-- user prepared statement!
          PARAM(oatpp::String, id)
    )

    QUERY(getAllUsers,
          "SELECT * FROM users LIMIT :limit OFFSET :offset;",
          PREPARE(true), //<-- user prepared statement!
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit)
    )

    QUERY(deleteUserById,
          "DELETE FROM users WHERE id=:id;",
          PREPARE(true), //<-- user prepared statement!
          PARAM(oatpp::String, id)
    )

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //AUTHORIZATION_MANAGEMENT_USERDB_H
