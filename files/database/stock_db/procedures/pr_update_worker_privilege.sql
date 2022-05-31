\c stock_db

CREATE OR REPLACE PROCEDURE PR_UPDATE_WORKER_PRIVILEGE(w_id int4, w_privilege int4)
AS $$
BEGIN
    UPDATE t_workers
    SET privilege_level = w_privilege
    WHERE pk = w_id;
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_UPDATE_WORKER_PRIVILEGE(int4, int4) TO workers_integrator;
