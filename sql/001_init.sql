CREATE TABLE IF NOT EXISTS users
(
    id       varchar(36) NOT NULL DEFAULT gen_random_uuid() PRIMARY KEY ,
    username varchar(255),
    email    varchar(255),
    is_admin boolean
);
