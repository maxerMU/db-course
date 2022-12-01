\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_WORKERS()
RETURNS TABLE (worker_id int4, name text, surname text, birthdate TIMESTAMP, privilege_level int4)
AS $$
BEGIN
    RETURN QUERY
        SELECT w.pk as worker_id, w.name, w.surname, w.birthdate, w.privilege_level
        FROM t_workers w;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_WORKERS() TO workers_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_WORKERS() TO stock_reader;