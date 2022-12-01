\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_DETAIL_BY_ID(part_name_ text)
RETURNS TABLE (part_name text, name_rus text, name_eng text, producer_id int4)
AS $$
BEGIN
    RETURN QUERY
        SELECT d.part_name, d.name_rus, d.name_eng, d.producer_id
        FROM t_details d
        WHERE d.part_name = part_name_;
END
$$ LANGUAGE PLPGSQL;

-- SELECT * FROM FN_GET_DETAIL_BY_ID(1);

GRANT EXECUTE ON FUNCTION FN_GET_DETAIL_BY_ID(text) TO details_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_DETAIL_BY_ID(text) TO stock_reader;