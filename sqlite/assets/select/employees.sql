SELECT a.id, first_name, last_name, a.id, address, phone, marital_status, group_concat(country_code, ';') AS country_code FROM employees e 
INNER JOIN additionally a on e.additionally_id = a.id LEFT JOIN additionally_country ac on a.id = ac.additionally_id
GROUP BY e.id;