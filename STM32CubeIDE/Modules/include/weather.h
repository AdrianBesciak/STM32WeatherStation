
typedef enum Weather_t {		//https://openweathermap.org/weather-conditions#Weather-Condition-Codes-2
	ASH,
	CLEAR,
	CLOUDS,
	DRIZZLE,
	DUST,
	FOG,
	HAZE,
	MIST,
	RAIN,
	SAND,
	SMOKE,
	SNOW,
	SQUALL,
	THUNDERSTORM,
	TORNADO
} Weather_t;


typedef struct weather_t {
	float * temp; //temperature in celsius
	Weather_t weatherMainName;
	char * weatherDescription;	//in PL
	float * pressure;	//hPa
	float * humidity;	//%
	float * visibility;	//m
	float * windSpeed;	//m/s
	float * rainfall;	//mm
	float * snowfall;	//mm
	char * city;
} weather_t;

extern weather_t weatherForecast;
