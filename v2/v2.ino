#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266HTTPClient.h>

DHT dht(D3, DHT11);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

String ssid = "Nombre del Wifi";
String password = "Clave del Wifi";

const char* serverName = "http://<url del servidor + el :puerto <ruta de donde escuchara el servidor>"; // Cambia la IP por la de tu servidor

float temp;
int hum;
unsigned long start_time;
const int pause = 5000;
boolean estado_imprimir = 1;
WiFiClient wifiClient;

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(2000);
  // start_time = millis();

  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Conectando....");
  lcd.setCursor(0, 1);
  lcd.print("Intento: ");

  int i = 1;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(10, 1);
    lcd.print(String(i));
    i++;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectado!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP().toString());
}

void loop() {
  if (millis() - start_time >= pause) {
    leerTemperatura();
    start_time = millis();
  }
}

void leerTemperatura() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //verificar datos de lectura
  if(isnan(temp) || isnan(hum)) {
    Serial.println("Error al leer datos");
    return;
  }

  enviarDatos();
  imprimir();
}

void imprimir() {
  if (estado_imprimir) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(ssid);
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP().toString());
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: " + String(temp) + " C");
    lcd.setCursor(0, 1);
    lcd.print("Humed: " + String(hum) + " %");
  }
  estado_imprimir = !estado_imprimir;
}

void enviarDatos() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wifiClient, serverName);

    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"temperatura\":\"" + String(temp) + "\",\"humedad\":\"" + String(hum) + "\"}";
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error en envío: ");
      Serial.println(httpResponseCode);

      // Ver más detalles del error
      switch (httpResponseCode) {
        case HTTPC_ERROR_CONNECTION_REFUSED:
          Serial.println("Error: Conexión rechazada");
          break;
        case HTTPC_ERROR_SEND_HEADER_FAILED:
          Serial.println("Error: Falló el envío de la cabecera");
          break;
        case HTTPC_ERROR_SEND_PAYLOAD_FAILED:
          Serial.println("Error: Falló el envío del payload");
          break;
        case HTTPC_ERROR_NOT_CONNECTED:
          Serial.println("Error: No conectado");
          break;
        case HTTPC_ERROR_CONNECTION_LOST:
          Serial.println("Error: Conexión perdida");
          break;
        case HTTPC_ERROR_NO_HTTP_SERVER:
          Serial.println("Error: No es un servidor HTTP");
          break;
        default:
          Serial.println("Error desconocido");
      }
    }
    http.end();
  } else {
    Serial.println("WiFi no está conectado");
  }
}
