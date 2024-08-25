#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define ENA D1 // Enable motor 1
#define IN1 D2 // Motor 1 input 1
#define IN2 D3 // Motor 1 input 2
#define IN3 D4 // Motor 2 input 1
#define IN4 D5 // Motor 2 input 2
#define ENB D6 // Enable motor 2
#define RAIN_SENSOR A0 // Pin sensor hujan analog

bool motorActivated = false;

const char* ssid = "Realme10"; // Ganti dengan SSID WiFi Anda
const char* password = "1234567899"; // Ganti dengan password WiFi Anda
const char* serverName = "http://your-api.org/post-esp-data.php"; // Ganti dengan URL endpoint API Anda

String apiKeyValue = "tPmAT5Ab3j7F9";
String sensorName = "Raindrops Module";

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(RAIN_SENSOR, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int rainValue = analogRead(RAIN_SENSOR);
  
  Serial.print("Nilai Sensor Hujan: ");
  Serial.println(rainValue);

  if (rainValue < 1024 && !motorActivated) {
   Serial.println("Hujan terdeteksi!");
    // Gerakkan motor 1 maju
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, 255);
    
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 255);

    delay(3910);

    // Berhenti setelah sebentar bergerak
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);

    motorActivated = true; // Set motor menjadi aktif
    Serial.println("Motor berhenti setelah sebentar bergerak");

    // POST data sensor ke web localhost
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName +  "&value1=" + String(rainValue) + "&statushujan=" + ("Hujan Turun") + "";
      Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
      
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Data terkirim ke server");
      } else {
        Serial.println("Gagal mengirim data");
      }
      http.end();
    }

  } else if (rainValue > 999 && motorActivated) {
   Serial.println("Tidak Ada Hujan");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 255);
    
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 255);

    delay(3900);

    // Berhenti setelah sebentar bergerak
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);

    motorActivated = false;

     // POST data sensor ke web localhost
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData =  "api_key=" + apiKeyValue + "&sensor=" + sensorName +  "&value1=" + String(rainValue) + "&statushujan=" + ("Tidak Hujan") + "";
      Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
      
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Data terkirim ke server");
      } else {
        Serial.println("Gagal mengirim data");
      }
      http.end();
    }
  }

  delay(1000); // Delay untuk membaca sensor secara periodik
}
