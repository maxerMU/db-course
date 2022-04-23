\c stock_db

CREATE OR REPLACE PROCEDURE PR_ADD_DETAIL(detail_part_name text, detail_name_rus text, detail_name_eng text, detail_producer_id int4)
AS $$
BEGIN
    INSERT INTO t_details(part_name, name_rus, name_eng, producer_id)
    VALUES (detail_part_name, detail_name_rus, detail_name_eng, detail_producer_id);
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_ADD_DETAIL(text, text, text, int4) TO details_integrator;
