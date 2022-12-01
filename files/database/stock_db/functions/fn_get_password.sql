\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_PASSWORD(username_arg text)
RETURNS TABLE (is_valid_user int4, worker_id int4, password text)
AS $$
DECLARE is_valid_var int4 := 0;
        worker_id_var int4 := 0;
        password_var text := '';
BEGIN
    SELECT a.pk, a.password INTO worker_id_var, password_var
    FROM T_WORKERS a -- TODO CHANGE TO VIEW
    WHERE a.username = username_arg;

    IF password_var IS NOT NULL THEN
        is_valid_var := 1;
    END IF;

    RETURN QUERY
        SELECT is_valid_var, worker_id_var, password_var;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_PASSWORD(text) TO workers_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_PASSWORD(text) TO stock_reader;