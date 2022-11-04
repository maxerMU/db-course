\c stock_db

CREATE OR REPLACE FUNCTION FN_ADD_WORKER(w_name text, w_surname text,
                                         w_birthdate TIMESTAMP, w_privilege_level int4,
                                         w_username text, w_password text)
RETURNS TABLE (return_code int4, worker_id int4)
AS $$
DECLARE return_code int4 := 0; -- 0 - OK; 1 - DUPLICATED
        is_unique int4 := 1;
BEGIN
    select 0 INTO is_unique
    FROM T_WORKERS
    WHERE username = w_username;

    IF is_unique = 0 THEN
        return_code := 1;
    ELSE
        return_code := 0;
        INSERT INTO t_workers(name, surname, birthdate, privilege_level, username, password)
        VALUES (w_name, w_surname, w_birthdate, w_privilege_level, w_username, w_password)
        RETURNING pk INTO worker_id;
    END IF;
    
    RETURN QUERY
        SELECT return_code as return_code, worker_id as worker_id;
END
$$ LANGUAGE PLPGSQL;

-- SELECT FN_ADD_WORKER('max', 'mitsevich', '2002-03-04', 1, 'maxermu', '123456');

GRANT EXECUTE ON FUNCTION FN_ADD_WORKER(text, text, TIMESTAMP, int4, text, text) TO workers_integrator;