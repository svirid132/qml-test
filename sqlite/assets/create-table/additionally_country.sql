CREATE TABLE "additionally_country" (
	"country_code"	INTEGER,
	"additionally_id"	INTEGER,
	FOREIGN KEY("country_code") REFERENCES "country"("code"),
	FOREIGN KEY("additionally_id") REFERENCES "additionally"("id")
)