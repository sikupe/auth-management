//
// Created by simon on 05.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_CONFIGPAIRDB_H
#define AUTHORIZATION_MANAGEMENT_CONFIGPAIRDB_H

#include "dto/ConfigPairRequest.h"
#include "dto/ConfigPair.h"
#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class ConfigPairDb : public oatpp::orm::DbClient {
public:
    explicit ConfigPairDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
            : oatpp::orm::DbClient(executor) {
    }

    QUERY(insertConfigPairsForPermissionProvider,
          "with config as ("
          "    INSERT INTO config_pairs (key, value) VALUES(:config.key, :config.value) RETURNING *"
          "),"
          "mapping as ("
          "    INSERT INTO permission_providers_config_pairs (config_pair_id, permission_provider_id) SELECT id, :permission_provider_id FROM config RETURNING *"
          ")"
          "SELECT * FROM config;",
          PREPARE(true),
          PARAM(oatpp::String, permission_provider_id),
          PARAM(oatpp::Object<ConfigPairRequest>, config)
    )

    QUERY(insertConfigPairsForPermission,
          "with config as ("
          "    INSERT INTO config_pairs (key, value) VALUES(:config.key, :config.value) RETURNING *"
          "),"
          "mapping as ("
          "    INSERT INTO permissions_config_pairs (config_pair_id, permission_id) SELECT id, :permission_id FROM config RETURNING *"
          ")"
          "SELECT * FROM config;",
          PREPARE(true),
          PARAM(oatpp::String, permission_id),
          PARAM(oatpp::Object<ConfigPairRequest>, config)
    )
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //AUTHORIZATION_MANAGEMENT_CONFIGPAIRDB_H
