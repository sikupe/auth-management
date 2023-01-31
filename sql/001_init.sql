CREATE TABLE IF NOT EXISTS users
(
    id       varchar(36)  NOT NULL DEFAULT gen_random_uuid() PRIMARY KEY,
    username varchar(255) NOT NULL,
    email    varchar(255) NOT NULL,
    is_admin boolean      NOT NULL
);

CREATE TABLE IF NOT EXISTS config_pairs
(
    id    varchar(36)  NOT NULL DEFAULT gen_random_uuid() PRIMARY KEY,
    key   varchar(255) NOT NULL,
    value varchar(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS permission_providers
(
    id   varchar(36) NOT NULL DEFAULT gen_random_uuid() PRIMARY KEY,
    type varchar(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS permissions
(
    id                     varchar(36)  NOT NULL DEFAULT gen_random_uuid() PRIMARY KEY,
    permission_provider_id varchar(36)  NOT NULL,
    name                   varchar(255) NOT NULL,
    description            varchar(255) NOT NULL,
    CONSTRAINT constraint_p_p_p_id FOREIGN KEY (permission_provider_id) REFERENCES permission_providers (id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS permission_providers_config_pairs
(
    permission_provider_id varchar(36) NOT NULL,
    config_pair_id         varchar(36) NOT NULL,
    CONSTRAINT p_p_c_p_primary PRIMARY KEY (permission_provider_id, config_pair_id),
    CONSTRAINT p_p_c_p_p_p_id FOREIGN KEY (permission_provider_id) REFERENCES permission_providers (id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT p_p_c_p_c_p_id FOREIGN KEY (config_pair_id) REFERENCES config_pairs (id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS permissions_config_pairs
(
    permission_id  varchar(36) NOT NULL,
    config_pair_id varchar(36) NOT NULL,
    CONSTRAINT p_c_p_primary PRIMARY KEY (permission_id, config_pair_id),
    CONSTRAINT p_p_c_p_p_p_id FOREIGN KEY (permission_id) REFERENCES permissions (id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT p_p_c_p_c_p_id FOREIGN KEY (config_pair_id) REFERENCES config_pairs (id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS permission_requests
(
    id                varchar(36) NOT NULL DEFAULT gen_random_uuid() PRIMARY KEY,
    requester         varchar(36) NOT NULL,
    request_date      int8        NOT NULL,
    invalidation_date int8        NOT NULL,
    permission_id     varchar(36) NOT NULL,
    status            varchar(50) NOT NULL DEFAULT 'Open',
    CONSTRAINT pr_requester FOREIGN KEY (requester) REFERENCES users (id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT pr_permission FOREIGN KEY (permission_id) REFERENCES permissions (id) ON DELETE CASCADE ON UPDATE CASCADE
);

