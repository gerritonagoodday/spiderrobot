    /////////////////////////////////////////////////////////////////
   //         ESP32 Weather Station Project     v1.00             //
  //       Get the latest version of the code here:              //
 //         http://educ8s.tv/esp32-weather-station              //
/////////////////////////////////////////////////////////////////


#define ARDUINOJSON_ENABLE_PROGMEM 0

#include "Adafruit_BME280.h" //https://github.com/Takatsuki0204/BME280-I2C-ESP32
#include <ArduinoJson.h>    //https://github.com/bblanchon/ArduinoJson
#include <WiFi.h>

const char* ssid     = "yourSSID";
const char* password = "yourPassword";
String CityID = "253394"; //Sparta, Greece
String APIKEY = "yourAPIkey";
#define ALTITUDE 216.0 // Altitude in Sparta, Greece

#define I2C_SDA 27
#define I2C_SCL 26
#define LED_PIN 2
#define BME280_ADDRESS 0x76  //If the sensor does not work, try the 0x77 address as well

float temperature = 0;
float humidity = 0;
float pressure = 0;
int weatherID = 0;

Adafruit_BME280 bme(I2C_SDA, I2C_SCL);

WiFiClient client;
char* servername ="api.openweathermap.org";  // remote server we will connect to
String result;

int  iterations = 1800;
String weatherDescription ="";
String weatherLocation = "";
float Temperature;

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(9600);

  initSensor();

  connectToWifi();
}

void loop() {
 
 delay(2000);

 if(iterations == 1800)//We check for updated weather forecast once every hour
 {
   getWeatherData();
   printWeatherIcon(weatherID);
   iterations = 0;   
 }

 getTemperature();
 sendTemperatureToNextion();
 
 getHumidity();
 sendHumidityToNextion();
 
 getPressure();
 sendPressureToNextion();

 iterations++;
 
 blinkLED();
}

void connectToWifi()
{
  WiFi.enableSTA(true);
  
  delay(2000);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

void initSensor()
{
  bool status = bme.begin(BME280_ADDRESS);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void blinkLED()
{
  digitalWrite(LED_PIN,HIGH);
  delay(100);
  digitalWrite(LED_PIN,LOW);
}

float getTemperature()
{
  temperature = bme.readTemperature();
}

float getHumidity()
{
  humidity = bme.readHumidity();
}

float getPressure()
{
  pressure = bme.readPressure();
  pressure = bme.seaLevelForAltitude(ALTITUDE,pressure);
  pressure = pressure/100.0F;
}

void getWeatherData() //client function to send/receive GET request data.
{
  String result ="";
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(servername, httpPort)) {
        return;
    }
      // We now create a URI for the request
    String url = "/data/2.5/forecast?id="+CityID+"&units=metric&cnt=1&APPID="+APIKEY;

       // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + servername + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server
    while(client.available()) {
        result = client.readStringUntil('\r');
    }

result.replace('[', ' ');
result.replace(']', ' ');

char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';

StaticJsonBuffer<1024> json_buf;
JsonObject &root = json_buf.parseObject(jsonArray);
if (!root.success())
{
  Serial.println("parseObject() failed");
}

String location = root["city"]["name"];
String temperature = root["list"]["main"]["temp"];
String weather = root["list"]["weather"]["main"];
String description = root["list"]["weather"]["description"];
String idString = root["list"]["weather"]["id"];
String timeS = root["list"]["dt_txt"];

weatherID = idString.toInt();
Serial.print("\nWeatherID: ");
Serial.print(weatherID);
endNextionCommand(); //We need that in order the nextion to recognise the first command after the serial print

}

void showConnectingIcon()
{
  Serial.println();
  String command = "weatherIcon.pic=3";
  Serial.print(command);
  endNextionCommand();
}

void sendHumidityToNextion()
{
  String command = "humidity.txt=\""+String(humidity,1)+"\"";
  Serial.print(command);
  endNextionCommand();
}

void sendTemperatureToNextion()
{
  String command = "temperature.txt=\""+String(temperature,1)+"\"";
  Serial.print(command);
  endNextionCommand();
}

void sendPressureToNextion()
{
  String command = "pressure.txt=\""+String(pressure,1)+"\"";
  Serial.print(command);
  endNextionCommand();
}

void endNextionCommand()
{
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void printWeatherIcon(int id)
{
 switch(id)
 {
  case 800: drawClearWeather(); break;
  case 801: drawFewClouds(); break;
  case 802: drawFewClouds(); break;
  case 803: drawCloud(); break;
  case 804: drawCloud(); break;
  
  case 200: drawThunderstorm(); break;
  case 201: drawThunderstorm(); break;
  case 202: drawThunderstorm(); break;
  case 210: drawThunderstorm(); break;
  case 211: drawThunderstorm(); break;
  case 212: drawThunderstorm(); break;
  case 221: drawThunderstorm(); break;
  case 230: drawThunderstorm(); break;
  case 231: drawThunderstorm(); break;
  case 232: drawThunderstorm(); break;

  case 300: drawLightRain(); break;
  case 301: drawLightRain(); break;
  case 302: drawLightRain(); break;
  case 310: drawLightRain(); break;
  case 311: drawLightRain(); break;
  case 312: drawLightRain(); break;
  case 313: drawLightRain(); break;
  case 314: drawLightRain(); break;
  case 321: drawLightRain(); break;

  case 500: drawLightRainWithSunOrMoon(); break;
  case 501: drawLightRainWithSunOrMoon(); break;
  case 502: drawLightRainWithSunOrMoon(); break;
  case 503: drawLightRainWithSunOrMoon(); break;
  case 504: drawLightRainWithSunOrMoon(); break;
  case 511: drawLightRain(); break;
  case 520: drawModerateRain(); break;
  case 521: drawModerateRain(); break;
  case 522: drawHeavyRain(); break;
  case 531: drawHeavyRain(); break;

  case 600: drawLightSnowfall(); break;
  case 601: drawModerateSnowfall(); break;
  case 602: drawHeavySnowfall(); break;
  case 611: drawLightSnowfall(); break;
  case 612: drawLightSnowfall(); break;
  case 615: drawLightSnowfall(); break;
  case 616: drawLightSnowfall(); break;
  case 620: drawLightSnowfall(); break;
  case 621: drawModerateSnowfall(); break;
  case 622: drawHeavySnowfall(); break;

  case 701: drawFog(); break;
  case 711: drawFog(); break;
  case 721: drawFog(); break;
  case 731: drawFog(); break;
  case 741: drawFog(); break;
  case 751: drawFog(); break;
  case 761: drawFog(); break;
  case 762: drawFog(); break;
  case 771: drawFog(); break;
  case 781: drawFog(); break;

  default:break; 
 }
}

void drawFog()
{
  String command = "weatherIcon.pic=13";
  Serial.print(command);
  endNextionCommand();
}

void drawHeavySnowfall()
{
  String command = "weatherIcon.pic=8";
  Serial.print(command);
  endNextionCommand();
}

void drawModerateSnowfall()
{
  String command = "weatherIcon.pic=8";
  Serial.print(command);
  endNextionCommand();
}

void drawLightSnowfall()
{
  String command = "weatherIcon.pic=11";
  Serial.print(command);
  endNextionCommand();
}

void drawHeavyRain()
{
  String command = "weatherIcon.pic=10";
  Serial.print(command);
  endNextionCommand();
}

void drawModerateRain()
{
  String command = "weatherIcon.pic=6";
  Serial.print(command);
  endNextionCommand();
}

void drawLightRain()
{
  String command = "weatherIcon.pic=6";
  Serial.print(command);
  endNextionCommand();
}

void drawLightRainWithSunOrMoon()
{
  String command = "weatherIcon.pic=7";
  Serial.print(command);
  endNextionCommand(); 
}
void drawThunderstorm()
{
  String command = "weatherIcon.pic=3";
  Serial.print(command);
  endNextionCommand();
}

void drawClearWeather()
{
  String command = "weatherIcon.pic=4";
  Serial.print(command);
  endNextionCommand();
}

void drawCloud()
{
  String command = "weatherIcon.pic=9";
  Serial.print(command);
  endNextionCommand();
}

void drawFewClouds()
{
  String command = "weatherIcon.pic=5";
  Serial.print(command);
  endNextionCommand(); 
}
