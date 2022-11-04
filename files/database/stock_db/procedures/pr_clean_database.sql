\c stock_db

CREATE OR REPLACE PROCEDURE PR_CLEAN_DATABASE()
AS $$
BEGIN
    TRUNCATE t_details, t_producers, t_stock, t_stock_log, t_swaps, t_tokens, t_workers CASCADE;
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_CLEAN_DATABASE() TO stock_adm;
