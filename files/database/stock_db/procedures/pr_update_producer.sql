\c stock_db

CREATE OR REPLACE PROCEDURE PR_UPDATE_PRODUCER(producer_id int4, producer_name text, producer_country text)
AS $$
BEGIN
    UPDATE t_producers
    SET name = producer_name, country = producer_country
    WHERE pk = producer_id;
END;
$$ LANGUAGE PLPGSQL;

CALL PR_UPDATE_PRODUCER(5, 'focus', 'pap pap');

GRANT EXECUTE ON PROCEDURE PR_UPDATE_PRODUCER(int4, text, text) TO producers_integrator;
