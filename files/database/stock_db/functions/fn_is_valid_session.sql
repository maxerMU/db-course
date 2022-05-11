\c stock_db

CREATE OR REPLACE FUNCTION FN_IS_VALID_SESSION(worker_id int4, token text)
RETURNS int4
AS $$
DECLARE is_valid int4;
BEGIN
    SELECT EXISTS (
        SELECT 1
        FROM t_tokens
        WHERE access_token = token and fk_worker = worker_id
    ) INTO is_valid;

    RETURN is_valid;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_IS_VALID_SESSION(int4, text) TO auth_integrator;