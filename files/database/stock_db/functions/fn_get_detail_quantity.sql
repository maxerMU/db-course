\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_DETAIL_QUANTITY(part_name_ text)
RETURNS int4
AS $$
DECLARE 
    quantity int4 := 0;
BEGIN
    SELECT s.quantity INTO quantity
    FROM t_stock s
    WHERE s.detail_part_name = part_name_;

    IF quantity IS NOT NULL THEN
        RETURN quantity;
    ELSE
        RETURN 0;
    END IF;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_DETAIL_QUANTITY(text) TO details_integrator;