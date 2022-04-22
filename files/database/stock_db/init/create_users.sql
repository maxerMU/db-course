CREATE USER stock_adm WITH ENCRYPTED PASSWORD 'stock_adm';
CREATE USER producers_integrator WITH ENCRYPTED PASSWORD 'producers_integrator';
CREATE USER details_integrator WITH ENCRYPTED PASSWORD 'details_integrator';

GRANT ALL PRIVILEGES ON DATABASE stock_db TO stock_adm;