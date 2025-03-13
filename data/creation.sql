pragma foreign_keys = true;

create table if not exists SERVICE(
    service_id integer primary key,
    name text unique not null,
    url text
);

create table if not exists LOGIN (
     login_id integer primary key,
     email text,
     password text,
     service_id int references SERVICE(service_id) on delete cascade
);

create table if not exists TOKEN(
    token_id integer primary key,
    login_id int references LOGIN(login_id) on delete cascade,
    value text not null,
    expired_at timestamp
);