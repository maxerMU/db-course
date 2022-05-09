\c stock_db

CREATE OR REPLACE PROCEDURE PR_ADD_SWAP(source_part_name text, destination_part_name text)
AS $$
BEGIN
    INSERT INTO t_swaps(source_detail, destination_detail)
    VALUES (source_part_name, destination_part_name);
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_ADD_SWAP(text, text) TO details_integrator;
