INSERT INTO "additionally" (address, phone, marital_status)
VALUES ("Вязов", "8 965 088 00 00", "Не женат");

CREATE TEMP TABLE _Variables(id_additionally INTEGER);

INSERT INTO _Variables(id_additionally) VALUES (last_insert_rowid());

INSERT INTO "employees"(first_name, last_name, additionally_id) 
VALUES (
        "Александр", "Свиридов", (SELECT * from _Variables)
);

INSERT INTO "additionally_country"(country_code, additionally_id) VALUES (643, (SELECT * from _Variables)),(895, (SELECT * from _Variables));

DROP TABLE _Variables;