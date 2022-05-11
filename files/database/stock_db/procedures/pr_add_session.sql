\c stock_db

CREATE OR REPLACE PROCEDURE PR_ADD_SESSION(worker_id int4, token text)
AS $$
BEGIN
    INSERT INTO t_tokens(access_token, fk_worker)
    VALUES (token, worker_id);
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_ADD_SESSION(int4, text) TO auth_integrator;