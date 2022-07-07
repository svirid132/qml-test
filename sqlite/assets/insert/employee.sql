INSERT INTO "additionally" (address, phone, marital_status)
VALUES ("%1", "%2", "%3");

CREATE TEMP TABLE _Variables(id_additionally INTEGER);

INSERT INTO _Variables(id_additionally) VALUES (last_insert_rowid());

INSERT INTO "employees"(first_name, last_name, additionally_id) 
VALUES (
        "%4", "%5", (SELECT * from _Variables)
);

-- Добавляем к additionally_country данные 
--должно выглядеть так INSERT INTO "additionally_country"(country_code, additionally_id) VALUES (643, (SELECT * from _Variables)),(895, (SELECT * from _Variables));
%6

DROP TABLE _Variables;