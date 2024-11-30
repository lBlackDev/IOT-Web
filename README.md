# Invernadero

## Descripción
El proyecto **Invernadero Dashboard** es una solución IoT para monitorear en tiempo real la temperatura y la humedad dentro de un invernadero. Utiliza un sensor DHT11 conectado a un ESP8266 que envía datos a un servidor Flask. Los datos se muestran en una página web utilizando Bootstrap y Chart.js para proporcionar un dashboard visual y fácil de entender.

## Características
- Monitoreo en tiempo real de la temperatura y la humedad.
- Visualización de datos en gráficos interactivos.
- Actualización automática de datos cada 3 segundos.
- Almacenamiento de datos en una base de datos MySQL cada 10 segundos.
- Interfaz web responsiva y estilizada con Bootstrap.

## Requisitos
- ESP8266
- Sensor DHT11
- Servidor Flask
- MySQL
- Librerías de Arduino: `ESP8266WiFi`, `DHT`, `LiquidCrystal_I2C`, `ESP8266HTTPClient`
- Librerías de Python: `Flask`, `Flask_SQLAlchemy`, `Flask_CORS`, `mysqlclient`

## Instalación

### Configuración del Hardware
1. Conecta el sensor DHT11 al ESP8266.
2. Configura la pantalla LCD I2C.

### Configuración del Software

#### ESP8266
1. Instala las librerías necesarias en el IDE de Arduino.
2. Sube el codigo ESP8266 


#### Servidor Flask
1. Clona este repositorio.
2. Crea y activa un entorno virtual.
    ```bash
    python -m venv venv
    source venv/bin/activate # En Windows, usa `venv\Scripts\activate`
    ```
3. Instala las dependencias.
    ```bash
    pip install -r requirements.txt
    ```
4. Configura la base de datos MySQL.
    ```sql
    CREATE DATABASE sensordata;
    USE sensordata;
    CREATE TABLE readings (
        id INT AUTO_INCREMENT PRIMARY KEY,
        humidity INT,
        temperature INT,
        timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );
    ```
5. Configura el archivo `config.py` con tu URI de conexión a MySQL.
    ```python
    class Config:
        SQLALCHEMY_DATABASE_URI = 'mysql://root:2154@localhost/sensordata'
        SQLALCHEMY_TRACK_MODIFICATIONS = False
    ```
6. Ejecuta el servidor Flask.
    ```bash
    python run.py
    ```

## Uso
1. Asegúrate de que el ESP8266 esté conectado a la misma red que el servidor Flask.
2. Abre tu navegador y navega a `http://<IP_DEL_SERVIDOR>:5000/`.
3. Monitorea los datos del invernadero en tiempo real.

## Contribución
Las contribuciones son bienvenidas. Por favor, abre un issue o envía un pull request.

## Licencia
Este proyecto está licenciado bajo la Licencia MIT. Para más detalles, consulta el archivo LICENSE.

## Contacto
Si tienes alguna pregunta o sugerencia, no dudes en contactarme en `rolando3365@gmail.com`.
