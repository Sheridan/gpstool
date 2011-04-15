CREATE TABLE "gpsdata"
(
	"gps_name"						TEXT NOT NULL,
	"timestamp"						REAL NOT NULL,
	"course_from_north"				REAL,
	"altitude"						REAL,
	"latitude"						REAL,
	"longitude"						REAL,
	"mode"							INTEGER,
	"status"						INTEGER,
	"speed_over_ground"				REAL,
	"position_quality_total"		REAL,
	"position_quality_horizontal"	REAL,
	"position_quality_vertical"		REAL,
	"satellites_in_last_fix"		INTEGER,
	"dop_spherical"					REAL,
	"dop_horizontal"				REAL,
	"dop_vertical"					REAL,
	"dop_time"						REAL,
	"dop_total_geometric"			REAL,
	"sentence"						TEXT
);

CREATE UNIQUE INDEX "gpsdata_gpsname_timestamp" on gpsdata (gps_name ASC, timestamp ASC);
CREATE INDEX		"gpsdata_gpsname"			on gpsdata (gps_name ASC);
CREATE INDEX		"gpsdata_timestamp"			on gpsdata (timestamp ASC);

CREATE TABLE "satellites"
(
	"gps_name"			TEXT NOT NULL,
	"timestamp"			REAL NOT NULL,
	"satprn"			INTEGER NOT NULL,
	"signal_strength"	INTEGER,
	"used_in_last_fix"	INTEGER,
	"azimuth"			INTEGER,
	"elevation"			INTEGER
);

CREATE UNIQUE INDEX "satellites_gpsname_timestamp_satprn"	on satellites (gps_name ASC, timestamp ASC, satprn ASC);
CREATE INDEX		"satellites_gpsname"					on satellites (gps_name ASC);
CREATE INDEX		"satellites_timestamp"					on satellites (timestamp ASC);
CREATE INDEX		"satellites_satprn"						on satellites (satprn ASC);
