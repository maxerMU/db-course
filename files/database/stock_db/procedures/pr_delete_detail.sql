\c stock_db

CREATE OR REPLACE PROCEDURE PR_DELETE_DETAIL(detail_part_name text)
AS $$
BEGIN
    DELETE FROM t_details
    WHERE part_name = detail_part_name;
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_DELETE_DETAIL(text) TO details_integrator;
