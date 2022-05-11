\c stock_db

DROP TABLE t_tokens;

CREATE TABLE t_tokens (
    access_token TEXT PRIMARY KEY,
    fk_worker INTEGER NOT NULL,

    FOREIGN KEY (fk_worker) REFERENCES T_WORKERS(pk) ON DELETE CASCADE
);