\c stock_db;

DROP TABLE IF EXISTS T_SWAPS;
DROP TABLE IF EXISTS T_STOCK;
DROP TABLE IF EXISTS T_DETAILS;
DROP TABLE IF EXISTS T_PRODUCERS;

CREATE table T_PRODUCERS (
    pk SERIAL PRIMARY KEY,
    name TEXT,
    country TEXT
);

CREATE table T_DETAILS (
    part_name TEXT PRIMARY KEY,
    name_rus TEXT,
    name_eng TEXT,

    producer_id INTEGER NOT NULL,
    FOREIGN KEY (producer_id) REFERENCES T_PRODUCERS(pk) ON DELETE CASCADE
);

CREATE table T_STOCK (
    pk SERIAL PRIMARY KEY,

    detail_part_name TEXT NOT NULL,
    quantity INTEGER not NULL,

    FOREIGN KEY (detail_part_name) REFERENCES T_DETAILS(part_name) ON DELETE CASCADE
);


CREATE table T_SWAPS (
    source_detail TEXT not NULL,
    destination_detail TEXT not NULL,

    FOREIGN KEY (source_detail) REFERENCES T_DETAILS(part_name) ON DELETE CASCADE,
    FOREIGN KEY (destination_detail) REFERENCES T_DETAILS(part_name) ON DELETE CASCADE
);