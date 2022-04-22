\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_ALL_PRODUCERS()
RETURNS TABLE (id int4, name text, country text)
AS $$
BEGIN
    RETURN QUERY
        SELECT p.pk, p.name, p.country
        FROM t_producers p;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_ALL_PRODUCERS() TO producers_integrator;