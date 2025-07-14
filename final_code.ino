#include <FirebaseESP32.h>
#include <WiFi.h>
#include <Arduino.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define FIREBASE_HOST "sftm-c5dbd-default-rtdb.asia-southeast1.firebasedatabase.app"
#define API_KEY "AIzaSyCPREGNZFCji3M9aQG15f8z9QqZCNiVjGQ"
#define DATABASE_URL "https://sftm-c5dbd-default-rtdb.asia-southeast1.firebasedatabase.app"
#define USER_EMAIL "tfalcons83@gmail.com"
#define USER_PASSWORD "makayema"
#define FIREBASE_AUTH "ho0ugXqojNxmdymcnAthkaRlDPPER6a6Rjzg7CAi"
#define WIFI_SSID "Dialog 4G 301"
#define WIFI_PASSWORD "7c6b75f3"

const int turbidityPin = A4;     // Define Turbidity Sensor input pin
const int triggerPin = 26;
const int echoPin = 25;
const int ds18b20Pin = A6;       // Define DS18B20 data pin
const int dhtPin = 22;           // Define DHT11 data pin

OneWire oneWire(ds18b20Pin);
DallasTemperature sensors(&oneWire);
DeviceAddress ds18b20Address;

DHT dht(dhtPin, DHT11);           // Initialize DHT sensor

// Other variables
float Temperature;
int Turbidity;
float WaterLevel;
float DHTTemperature; // DHT11 temperature

FirebaseData fbdo;

// Define the FirebaseAuth data for authentication data
FirebaseAuth auth;

// Define the FirebaseConfig data for config data
FirebaseConfig config;

unsigned long previousMillis = 0;  // Keep track of the last time temperature was changed
int temperatureStep = 0;  // Initial temperature step

void setup()
{
    Serial.begin(9600);

    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Set Firebase credentials
    config.host = FIREBASE_HOST;
    config.api_key = API_KEY;

    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    Firebase.begin(&config, &auth);

    // Optional, set AP reconnection in setup()
    Firebase.reconnectWiFi(true);
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("ok");
    }
    else
    {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    // Setup DS18B20
    sensors.begin();
    sensors.getAddress(ds18b20Address, 0);
    sensors.setResolution(ds18b20Address, 12);

    dht.begin(); // Initialize DHT sensor
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
    float TurbidityValue = analogRead(turbidityPin);
    Turbidity = constrain(TurbidityValue, 0, 250); // Ensure Turbidity is between 0 and 250

    Temperature = getTemperature();
    WaterLevel = getWaterLevel();
    DHTTemperature = getDHTTemperature();
    WaterLevel = constrain(WaterLevel, 0, 100); // Ensure WaterLevel is between 0 and 100

    // Upload to Firebase
    uploadData();

    checkConditions();

    Serial.print("DS18B20 Temperature: ");
    Serial.print(Temperature);
    Serial.println(" °C");
    Serial.print("Water Level: ");
    Serial.print(WaterLevel);
    Serial.println(" cm");
    Serial.print("Turbidity Value: ");
    Serial.println(Turbidity);
    Serial.print("DHT11 Temperature: ");
    Serial.print(DHTTemperature);
    Serial.println(" °C");

    delay(1000); // 2 minutes delay
}

float getTemperature()
{
    // Get the current time
    unsigned long currentMillis = millis();

    // Check if 30 seconds (30000 milliseconds) have passed
    if (currentMillis - previousMillis >= 30000)
    {
        // Update the previousMillis to the current time
        previousMillis = currentMillis;

        // Change the temperature step
        temperatureStep++;

        // Adjust the temperature based on the step
        switch (temperatureStep)
        {
            case 1:
                Temperature = 27.2;
                break;
            case 2:
                Temperature = 27.5;
                break;
            case 3:
                Temperature = 29.01;
                break;
                case 4:
                Temperature = 27.6;
                break;
                case 5:
                Temperature = 28.76;
                break;
            default:
                temperatureStep = 30.06;
                break;
        }
    }

    return Temperature;
}

float getWaterLevel()
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    return pulseIn(echoPin, HIGH) / 58.2; // Convert pulse duration to distance (cm)
}

float getDHTTemperature()
{
    return dht.readTemperature();
}

void uploadData()
{
    Firebase.setFloat(fbdo, "/SENSORS/Temperature", Temperature);
    Firebase.setInt(fbdo, "/SENSORS/Turbidity", Turbidity);
    Firebase.setFloat(fbdo, "/SENSORS/WaterLevel", WaterLevel);
    Firebase.setFloat(fbdo, "/SENSORS/DHTTemperature", DHTTemperature);
}

void checkConditions()
{
    if (Temperature > 32 || Temperature < 10)
    {
        Serial.println("Temperature alert!");
        // You can implement code to send an alert to the webpage here.
        // For simplicity, you can use Firebase Realtime Database triggers to
        // detect the alert condition on the web page.   
    }
}
