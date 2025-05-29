#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Servo.h>

// DHT11 sensor pin
#define DHT11_PIN D4 // Define the pin connected to the sensor
#define SERVO_PIN D3 // Define the pin connected to the servo
#define BUZZER_PIN D2 // Define the pin connected to the buzzer

DHT dht(DHT11_PIN, DHT11);
Servo myservo;

float temp, humi;
char temperatureTemp[7];
char humidityTemp[7];
char heatIndexTemp[7];

// WiFi and MQTT configurations
const char* ssid = "SLT_FIBRE_2545850";
const char* password = "UH2545850Kasthu";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* clientId = "thermosense_client";

const char* temp_topic = "sensor/dht11/temperature";
const char* humi_topic = "sensor/dht11/humidity";
const char* heat_index_topic = "sensor/dht11/heatindex";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Turn off the onboard LED

  myservo.attach(SERVO_PIN); // Attach the servo to the pin
  pinMode(BUZZER_PIN, OUTPUT); // Initialize the buzzer pin

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  
  Serial.println("Connected to the WiFi network");
  
  // Connect to MQTT Broker
  client.setServer(mqttServer, mqttPort);
  Serial.println("Connecting to MQTT Broker...");
  
  while (!client.connected()) {
    if (client.connect(clientId)) {
      Serial.println("Connected to MQTT Broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
  
  dht.begin();
  Serial.println("DHT sensor initialized");
}

void loop() {
  delay(3000);

  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Convert Celsius to Fahrenheit
  float temp_f = (temperatureC * 9.0) / 5.0 + 32.0;

  // Heat Index Calculation
  float heatIndex = -42.379 + 2.04901523 * temp_f + 10.14333127 * humidity - 0.22475541 * temp_f * humidity - 
                      0.00683783 * temp_f * temp_f - 0.05481717 * humidity * humidity +
                      0.00122874 * temp_f * temp_f * humidity + 0.00085282 * temp_f * humidity * humidity - 
                      0.00000199 * temp_f * temp_f * humidity * humidity;


  dtostrf(temperatureC, 6, 2, temperatureTemp);
  dtostrf(humidity, 6, 2, humidityTemp);
  dtostrf(heatIndex, 6, 2, heatIndexTemp);

  client.publish(temp_topic, temperatureTemp);
  client.publish(humi_topic, humidityTemp);
  client.publish(heat_index_topic, heatIndexTemp);

  Serial.println("Temperature: " + String(temperatureC) + "°C - Humidity: " + String(humidity) + "% - Heat Index: " + String(heatIndex));

  checkHeatIndexLevels(heatIndex);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void checkHeatIndexLevels(float heatIndex) {
  if (heatIndex <= 80) {
    Serial.println("Heat Index: Comfortable");
    myservo.write(0); // Set servo to 0 degrees
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer

  } else if (heatIndex <= 90) {
    Serial.println("Heat Index: Caution");
    myservo.write(45); // Set servo to 45 degrees
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer

  } else if (heatIndex <= 103) {
    Serial.println("Heat Index: Hot");
    myservo.write(90); // Set servo to 90 degrees
    digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer

  } else if (heatIndex <= 124) {
    Serial.println("Heat Index: Very Hot");
    myservo.write(135); // Set servo to 135 degrees
    digitalWrite(BUZZER_PIN, HIGH); // Turn off the 
    
  } else {
    Serial.println("Heat Index: Dangerous");
    myservo.write(180); // Set servo to 180 degrees
    digitalWrite(BUZZER_PIN, HIGH); // Turn off the buzzer
  }
}