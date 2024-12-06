from flask import request, jsonify, render_template, current_app as app
from datetime import datetime, timedelta
import pytz
from .models import db, SensorData, Riego

@app.route('/update', methods=['POST']) # Ruta para Mostrar los datos en la Web
def update_data():
    data = request.get_json()
    temperature = data['temperatura']
    humidity = data['humedad']

    response = {
        'message': 'Data recibidos y actualizados',
        'temperatura': temperature,
        'humedad': humidity
    }

    return jsonify(response)

last_saved_time = datetime.utcnow()  # Tiempo inicial

@app.route('/db_update', methods=['POST'])
def db_update():
    global last_saved_time
    data = request.get_json()
    temperature = data['temperatura']
    humidity = data['humedad']

    current_time = datetime.utcnow()
    if current_time - last_saved_time >= timedelta(seconds=10):
        new_data = SensorData(temperature=temperature, humidity=humidity)
        db.session.add(new_data)
        db.session.commit()
        last_saved_time = current_time

        response = {
            'message': 'Datos guardados en la base de datos',
            'temperatura': temperature,
            'humedad': humidity
        }
    else:
        response = {
            'message': 'Datos no guardados, aún no han pasado 10 segundos'
        }

    return jsonify(response)

@app.route('/api/latest_data', methods=['GET'])
def get_latest_data():
    latest_data = SensorData.query.order_by(SensorData.timestamp.desc()).first()
    if latest_data:
        data = {
            'temperature': latest_data.temperature,
            'humidity': latest_data.humidity,
            'timestamp': latest_data.timestamp
        }
        print(data)
        return jsonify(data)
    else:
        return jsonify({'error': 'Dato no disponible'})

@app.route('/')
def index():
    latest_data = SensorData.query.order_by(SensorData.timestamp.desc()).first()
    return render_template('index.html', data=latest_data)

#ruta para guardar la configuracion del riego
@app.route('/guardar_configuracion_riego', methods=['POST'])
def guardar_configuracion_riego():
    data = request.get_json()
    hora_inicio = data['hora_inicio']
    hora_fin = data['hora_fin']
    dias = ",".join(data['dias'])  # Concatena los días seleccionados en una cadena separada por comas

    nuevo_riego = Riego(hora_inicio=hora_inicio, hora_fin=hora_fin, dias=dias)
    db.session.add(nuevo_riego)
    db.session.commit()

    response = {
        'message': 'Configuracion de riego guardada exitosamente'
    }
    return jsonify(response)

#ruta para ver estado del riego
@app.route('/api/estado_riego', methods=['GET'])
def estado_riego():
    ahora = datetime.now().time()

    riego_activo = Riego.query.filter(
        Riego.hora_inicio <= ahora,
        Riego.hora_fin >= ahora,
    ).first()

    estado = "Activado" if riego_activo else "Apagado"
    print("Hora actual:", ahora)
    print("Hora de inicio:", riego_activo.hora_inicio if riego_activo else "No hay riego activo")
    return jsonify({'estado' : estado})

@app.route('/get/temperatura_optima', methods=['GET'])
def temperatura_optima():
    ultima_medicion = SensorData.query.order_by(SensorData.timestamp.desc()).first()
    if ultima_medicion:
        data = {
            'temperature' :ultima_medicion.temperature,
            'humidity' :ultima_medicion.humidity,
            'timestamp': ultima_medicion.timestamp
        }
    print(data)
    return jsonify(data)

