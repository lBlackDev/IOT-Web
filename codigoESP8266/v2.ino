#include <ESP8266WiFi.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266HTTPClient.h>

// Configuración del sensor DHT11
DHT dht(D3, DHT11);

// Configuración de la pantalla LCD I2C
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Configuración de la red WiFi
const char* ssid = "nombre_de_la_red_wifi";           // Cambia por tu SSID
const char* password = "Clave_de_la_red_wifi";         // Cambia por tu contraseña

// Dirección del servidor Flask
// Usar la misma red entre el servidor y el esp8266
const char* serverName = "http://192.168.1.12:5000/update"; // Verifica la IP y puerto del servidor Flask
const char* dbServerName = "http://192.168.1.12:5000/db_update"; // Verifica la IP y puerto del servidor Flask para BD

// Variables para los datos del sensor
float temp = 0.0;
int hum = 0;

// Control del tiempo entre lecturas
unsigned long lastReadTime = 0;
unsigned long lastDBUpdateTime = 0;
const int readInterval = 3000; // Intervalo en milisegundos (3 segundos)
const int dbInterval = 10000;  // Intervalo en milisegundos (10 segundos)

// Alterna entre mostrar datos y estado de conexión
boolean estado_imprimir = true;

// Cliente WiFi
WiFiClient wifiClient;

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serie
  dht.begin();          // Inicializa el sensor DHT11
  lcd.init();           // Inicializa la pantalla LCD
  lcd.backlight();

  // Conexión a WiFi
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi...");
  WiFi.begin(ssid, password);

  int intento = 1;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Intento: ");
    lcd.print(intento++);
  }

  // Mensaje de éxito al conectar
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectado!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP().toString());
  delay(2000);
}

void loop() {
  // Lee los datos del sensor cada 3 segundos
  if (millis() - lastReadTime >= readInterval) {
    lastReadTime = millis();
    leerTemperatura();
    enviarDatos();
  }

  // Envía datos a la base de datos cada 10 segundos
  if (millis() - lastDBUpdateTime >= dbInterval) {
    lastDBUpdateTime = millis();
    enviarDatosBD();
  }
}

void leerTemperatura() {
  // Lee temperatura y humedad
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  // Verifica si la lectura es válida
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Error al leer datos del sensor");
    return;
  }

  // Mostrar datos en la pantalla LCD
  imprimir();
}

void imprimir() {
  lcd.clear();
  if (estado_imprimir) {
    lcd.setCursor(0, 0);
    lcd.print("Conectado a:");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP().toString());
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: " + String(temp) + " C");
    lcd.setCursor(0, 1);
    lcd.print("Humed: " + String(hum) + " %");
  }
  estado_imprimir = !estado_imprimir; // Alterna la impresión
}

void enviarDatos() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Inicia la conexión con el servidor Flask
    http.begin(wifiClient, serverName);
    http.addHeader("Content-Type", "application/json");

    // Prepara los datos en formato JSON
    String httpRequestData = "{\"temperatura\": " + String(temp) + ", \"humedad\": " + String(hum) + "}";
    Serial.println("Enviando datos: " + httpRequestData);

    // Envía los datos al servidor Flask
    int httpResponseCode = http.POST(httpRequestData);

    // Manejo de la respuesta del servidor
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Código de respuesta: " + String(httpResponseCode));
      Serial.println("Respuesta del servidor: " + response);
    } else {
      Serial.println("Error al enviar datos: " + String(httpResponseCode));
    }

    // Finaliza la conexión HTTP
    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }
}

void enviarDatosBD() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Inicia la conexión con el servidor Flask para la base de datos
    http.begin(wifiClient, dbServerName);
    http.addHeader("Content-Type", "application/json");

    // Prepara los datos en formato JSON
    String httpRequestData = "{\"temperatura\": " + String(temp) + ", \"humedad\": " + String(hum) + "}";
    Serial.println("Enviando datos a BD: " + httpRequestData);

    // Envía los datos al servidor Flask para la base de datos
    int httpResponseCode = http.POST(httpRequestData);

    // Manejo de la respuesta del servidor
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Código de respuesta BD: " + String(httpResponseCode));
      Serial.println("Respuesta del servidor BD: " + response);
    } else {
      Serial.println("Error al enviar datos a BD: " + String(httpResponseCode));
    }

    // Finaliza la conexión HTTP
    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }
}
