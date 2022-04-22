\c stock_db

CREATE OR REPLACE PROCEDURE PR_DELETE_PRODUCER(producer_id int4)
AS $$
BEGIN
    DELETE FROM t_producers
    WHERE pk = producer_id;
END;
$$ LANGUAGE PLPGSQL;

-- CALL PR_DELETE_PRODUCER(1002);

GRANT EXECUTE ON PROCEDURE PR_DELETE_PRODUCER(int4) TO producers_integrator;
