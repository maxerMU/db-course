\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_WORKER_BY_ID(worker_id int4)
RETURNS TABLE (name text, surname text, birthdate TIMESTAMP, privilege_level int4)
AS $$
BEGIN
    RETURN QUERY
        SELECT w.name, w.surname, w.birthdate, w.privilege_level
        FROM t_workers w
        WHERE w.pk = worker_id;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_WORKER_BY_ID(int4) TO workers_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_WORKER_BY_ID(int4) TO stock_reader;