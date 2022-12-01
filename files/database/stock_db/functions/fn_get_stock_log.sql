\c stock_db

CREATE OR REPLACE FUNCTION FN_GET_STOCK_LOG(time_start timestamp, time_end timestamp)
RETURNS TABLE (fk_worker int4, 
               fk_detail text,
               change int4,
               change_time timestamp)
AS $$
BEGIN
    RETURN QUERY
        SELECT sl.fk_worker as fk_worker, sl.fk_detail as fk_detail, sl.change as change, sl.change_time as change_time
        FROM t_stock_log sl
        WHERE cast(sl.change_time as DATE) >= time_start and cast(sl.change_time as DATE) <= time_end;
END
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON FUNCTION FN_GET_STOCK_LOG(timestamp, timestamp) TO stock_integrator;
GRANT EXECUTE ON FUNCTION FN_GET_STOCK_LOG(timestamp, timestamp) TO stock_reader;