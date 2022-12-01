\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_ALL_DETAILS()
RETURNS TABLE (part_name text, name_rus text, name_eng text, producer_id int4)
AS $$
BEGIN
    RETURN QUERY
        SELECT d.part_name, d.name_rus, d.name_eng, d.producer_id
        FROM t_details d;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_ALL_DETAILS() TO details_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_ALL_DETAILS() TO stock_reader;