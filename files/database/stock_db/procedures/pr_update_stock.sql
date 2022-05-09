\c stock_db

CREATE OR REPLACE PROCEDURE PR_UPDATE_STOCK(part_name text, worker_id int4, qty int4)
AS $$
BEGIN
    INSERT INTO T_STOCK(detail_part_name, quantity)
    VALUES (part_name, qty)
    ON CONFLICT(detail_part_name) DO UPDATE
    SET quantity = t_stock.quantity + qty;

    INSERT INTO T_STOCK_LOG(fk_worker, fk_detail, change)
    VALUES (worker_id, part_name, qty);
END;
$$ LANGUAGE PLPGSQL;

GRANT EXECUTE ON PROCEDURE PR_UPDATE_STOCK(text, int4, int4) TO stock_integrator;