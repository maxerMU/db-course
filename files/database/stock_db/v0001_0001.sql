\c stock_db;

DROP TABLE T_STOCK_LOG;
DROP VIEW V_WORKERS_COMMON;
DROP VIEW V_WORKERS_AUTH;
DROP TABLE T_WORKERS;

CREATE table T_WORKERS (
    pk SERIAL PRIMARY KEY,
    name TEXT,
    surname TEXT,
    birthdate TIMESTAMP,
    privilege_level INT NOT NULL,
    username TEXT,
    password TEXT
);

CREATE VIEW V_WORKERS_COMMON AS
SELECT pk, name, surname, birthdate, privilege_level
FROM T_WORKERS;

CREATE VIEW V_WORKERS_AUTH AS
SELECT pk, username, password
FROM T_WORKERS;

CREATE table T_STOCK_LOG (
    pk SERIAL PRIMARY KEY,
    fk_worker INTEGER NOT NULL,
    fk_detail TEXT NOT NULL,
    change INT NOT NULL,

    change_time TIMESTAMP DEFAULT NOW(),

    FOREIGN KEY (fk_worker) REFERENCES T_WORKERS(pk) ON DELETE CASCADE,
    FOREIGN KEY (fk_detail) REFERENCES T_DETAILS(part_name) ON DELETE CASCADE
)