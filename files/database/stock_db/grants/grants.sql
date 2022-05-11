\c stock_db;

GRANT USAGE ON SEQUENCE t_producers_pk_seq TO stock_adm;
GRANT USAGE ON SEQUENCE t_workers_pk_seq TO stock_adm;
GRANT USAGE ON SEQUENCE t_stock_log_pk_seq TO stock_adm;

GRANT ALL ON TABLE T_PRODUCERS TO stock_adm;
GRANT ALL ON TABLE T_DETAILS TO stock_adm;
GRANT ALL ON TABLE T_STOCK TO stock_adm;
GRANT ALL ON TABLE T_SWAPS TO stock_adm;
GRANT ALL ON TABLE T_WORKERS TO stock_adm;
GRANT ALL ON TABLE T_STOCK_LOG TO stock_adm;
GRANT ALL ON TABLE T_TOKENS TO stock_adm;

GRANT USAGE ON SEQUENCE t_producers_pk_seq TO producers_integrator;
GRANT ALL ON TABLE T_PRODUCERS TO producers_integrator;

GRANT ALL ON TABLE T_DETAILS TO details_integrator;
GRANT ALL ON TABLE T_SWAPS TO details_integrator;

GRANT USAGE ON SEQUENCE t_stock_log_pk_seq TO stock_integrator;
GRANT ALL ON TABLE T_STOCK TO stock_integrator;
GRANT ALL ON TABLE T_STOCK_LOG TO stock_integrator;

GRANT USAGE ON SEQUENCE t_workers_pk_seq TO workers_integrator;
GRANT ALL ON TABLE T_WORKERS TO workers_integrator;

GRANT ALL ON TABLE T_TOKENS to auth_integrator;
-- GRANT ALL ON VIEW V_WORKERS_COMMON TO workers_integrator;
-- GRANT ALL ON VIEW V_WORKERS_AUTH TO workers_integrator;