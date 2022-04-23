\c stock_db

CREATE OR REPLACE PROCEDURE PR_UPDATE_DETAIL(detail_part_name text, detail_name_rus text, detail_name_eng text, detail_producer_id int4)
AS $$
BEGIN
    UPDATE t_details
    SET name_rus = detail_name_rus, name_eng = detail_name_eng, producer_id = detail_producer_id
    WHERE part_name = detail_part_name;
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_UPDATE_DETAIL(text, text, text, int4) TO details_integrator;
