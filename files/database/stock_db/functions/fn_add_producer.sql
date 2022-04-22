\c stock_db

CREATE OR REPLACE FUNCTION FN_ADD_PRODUCER(producer_name text, producer_country text)
RETURNS int4
AS $$
DECLARE producer_id int4;
BEGIN
    INSERT INTO t_producers(name, country)
    VALUES (producer_name, producer_country)
    RETURNING pk INTO producer_id;

    RETURN producer_id;
END
$$ LANGUAGE PLPGSQL;

-- SELECT FN_ADD_PRODUCER('ford focus', 'rus');

GRANT EXECUTE ON FUNCTION FN_ADD_PRODUCER(text, text) TO producers_integrator;