\c stock_db

CREATE OR REPLACE PROCEDURE PR_DELETE_SWAP(source_part_name text, destination_part_name text)
AS $$
BEGIN
    DELETE FROM t_swaps
    WHERE source_detail = source_part_name and destination_detail = destination_part_name;
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_DELETE_SWAP(text, text) TO details_integrator;
