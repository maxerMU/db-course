\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_PRODUCER_BY_ID(producer_id int4)
RETURNS TABLE (id int4, name text, country text)
AS $$
BEGIN
    RETURN QUERY
        SELECT p.pk, p.name, p.country
        FROM t_producers p
        WHERE p.pk = producer_id;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_PRODUCER_BY_ID(int4) TO producers_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_PRODUCER_BY_ID(int4) TO stock_reader;