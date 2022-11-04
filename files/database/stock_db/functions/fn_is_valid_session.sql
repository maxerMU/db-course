\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_SESSION_DATA(token text)
RETURNS TABLE (is_valid_session int4, worker_id int4)
AS $$
DECLARE is_valid_var int4 := 1;
        worker_id_var int4;
BEGIN
    SELECT t.fk_worker INTO worker_id_var
    FROM t_tokens
    WHERE access_token = token;

    IF worker_id_var is NULL THEN
        is_valid_var := 0;
    END IF;

    RETURN QUERY
        SELECT is_valid_var, worker_id_var;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_SESSION_DATA(text) TO auth_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_SESSION_DATA(text) TO stock_reader;