UPDATE employees 
SET first_name = 'Михаил',
last_name = 'Чехов'
where id = 1;

UPDATE 	additionally
set address = "Крыленко",
phone = "8 965 088 00 00",
marital_status = "Не женат"
where id = 1;

DELETE FROM additionally_country
WHERE additionally_id = 1;

INSERT INTO additionally_country(country_code, additionally_id) 
VALUES (31, 133), (40, 133);