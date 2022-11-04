\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_SWAPS(detail_part_name text)
RETURNS TABLE (part_name text)
AS $$
BEGIN
    RETURN QUERY
        SELECT s.destination_detail
        FROM t_swaps s
        WHERE s.source_detail = detail_part_name;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_SWAPS(text) TO details_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_SWAPS(text) TO stock_integrator;