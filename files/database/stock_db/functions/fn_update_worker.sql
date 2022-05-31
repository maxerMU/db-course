\c stock_db

CREATE OR REPLACE FUNCTION FN_UPDATE_WORKER(w_id int4, w_name text, w_surname text,
                                             w_birthdate TIMESTAMP, w_username text, w_password text)
RETURNS int4
AS $$
DECLARE return_code int4 := 0; -- 0 - OK; 1 - DUPLICATED
        is_unique int4 := 1;
BEGIN
    select 0 INTO is_unique
    FROM T_WORKERS
    WHERE username = w_username and pk != w_id;

    IF is_unique = 0 THEN
        return_code := 1;
    ELSE
        return_code := 0;
        UPDATE t_workers
        SET name = w_name, surname = w_surname, birthdate = w_birthdate, username = w_username, password = w_password
        WHERE pk = w_id;
    END IF;
    
    RETURN return_code;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_UPDATE_WORKER(int4, text, text, TIMESTAMP, text, text) TO workers_integrator;
