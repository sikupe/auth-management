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

    QUERY(getConfigPairsForPermissionProvider,
          "SELECT key, value FROM config_pairs INNER JOIN permission_providers_config_pairs ON permission_providers_config_pairs.config_pair_id = config_pairs.id WHERE permission_providers_config_pairs.permission_provider_id = :permission_provider_id",
          PREPARE(true),
          PARAM(oatpp::String, permission_provider_id)
    )

    QUERY(getConfigPairsForPermission,
          "SELECT key, value FROM config_pairs INNER JOIN permissions_config_pairs ON permissions_config_pairs.config_pair_id = config_pairs.id WHERE permissions_config_pairs.permission_id = :permission_id",
          PREPARE(true),
          PARAM(oatpp::String, permission_id)
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

    QUERY(deleteConfigPairsForPermissionProvider,
          "DELETE FROM config_pairs JOIN permission_providers_config_pairs ON permission_providers_config_pairs.permission_provider_id = config_pairs.config_pair_id WHERE config_pairs.permission_provider_id = :permission_provider_id",
          PREPARE(true),
          PARAM(oatpp::String, permission_provider_id)
    )

    QUERY(deleteConfigPairsForPermission,
          "DELETE FROM config_pairs JOIN permissions_config_pairs ON permissions_config_pairs.permission_id = config_pairs.config_pair_id WHERE config_pairs.permission_id = :permission_id",
          PREPARE(true),
          PARAM(oatpp::String, permission_id)
    )
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //AUTHORIZATION_MANAGEMENT_CONFIGPAIRDB_H
