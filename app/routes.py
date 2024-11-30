from flask import request, jsonify, render_template, current_app as app
from datetime import datetime
from .models import db, SensorData

@app.route('/update', methods=['POST']) # Ruta para Mostrar los datos en la Web
def update_data():
    data = request.get_json()
    temperature = data['temperatura']
    humidity = data['humedad']
    
    response = {
        'message': 'Data received and updated',
        'temperature': temperature,
        'humidity': humidity
    }
    
    return jsonify(response)


@app.route('/db_update', methods=['POST']) # Ruta para guardar el dato cada 10sg en la BD
def db_update():
    data = request.get_json()
    temperature = data['temperatura']
    humidity = data['humedad']
    
    new_data = SensorData(temperature=temperature, humidity=humidity)
    db.session.add(new_data)
    db.session.commit()
    
    response = {
        'message': 'Data stored in database',
        'temperature': temperature,
        'humidity': humidity
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
        return jsonify(data)
    else:
        return jsonify({'error': 'No data available'})



@app.route('/')
def index():
    latest_data = SensorData.query.order_by(SensorData.timestamp.desc()).first()
    return render_template('index.html', data=latest_data)
