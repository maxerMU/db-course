\c stock_db

CREATE OR REPLACE FUNCTION FN_STOCK_CURRENT_DETAILS()
RETURNS TABLE (part_number text, quantity int4)
AS $$
BEGIN
    RETURN QUERY
        SELECT s.detail_part_name as part_number, s.quantity as quantity
        FROM t_stock s
        WHERE s.quantity != 0;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_STOCK_CURRENT_DETAILS() TO stock_integrator;
GRANT EXECUTE ON FUNCTION FN_STOCK_CURRENT_DETAILS() TO stock_reader;