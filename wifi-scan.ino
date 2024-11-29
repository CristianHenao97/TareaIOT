#include <WiFi.h>
#include <HTTPClient.h>

// Credenciales de WiFi simuladas (no se usan en Wokwi)
const char* ssid = "SSID";
const char* password = "PWD";

// Configuración de la API de WhatsApp de CallMeBot
String phoneNumber = "+573046407997"; // Tu número de WhatsApp
String apiKey = "apiKey";            // Reemplaza con tu API key de CallMeBot

// Pin del sensor simulado
const int simulatedSensor = 36; // Conecta el potenciómetro a este pin en Wokwi
int previousValue = 0;

// Función para enviar una notificación usando CallMeBot
void sendNotification(String message) {
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + message;    
  HTTPClient http;
  http.begin(url);

  // Realiza una solicitud GET a la API
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    Serial.println("Notificación enviada con éxito");
  } else {
    Serial.println("Error al enviar la notificación");
    Serial.print("Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void setup() {
  Serial.begin(115200);

  // Simulación de conexión WiFi
  Serial.println("Simulando conexión WiFi...");
  delay(1000); // Simula el tiempo de conexión
  Serial.println("Conectado a WiFi simulado!");
}

void loop() {
  // Lee el valor del sensor simulado
  int sensorValue = analogRead(simulatedSensor);

  // Detecta cambios significativos en el valor del sensor
  if (abs(sensorValue - previousValue) > 50) { // Umbral para detectar cambios
    String message = "El valor del sensor cambió significativamente: " + String(sensorValue);
    sendNotification(message);
    previousValue = sensorValue;
  }

  delay(500); // Retardo para la simulación
}
