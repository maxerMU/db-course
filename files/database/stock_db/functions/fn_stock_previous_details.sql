\c stock_db

CREATE OR REPLACE FUNCTION FN_STOCK_PREVIOUS_DETAILS()
RETURNS TABLE (part_number text)
AS $$
BEGIN
    RETURN QUERY
        SELECT s.detail_part_name as part_number
        FROM t_stock s
        WHERE s.quantity = 0;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_STOCK_PREVIOUS_DETAILS() TO stock_integrator;