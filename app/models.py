from . import db
from datetime import datetime, timezone

class SensorData(db.Model):
    __tablename__ = 'readings'  # Asegúrate de que el nombre de la tabla coincide
    id = db.Column(db.Integer, primary_key=True)
    temperature = db.Column(db.Float, nullable=False)
    humidity = db.Column(db.Float, nullable=False)
    # por lo general en el default = se usaba 'datetime.utcnow()'
    # ahora se utiliza datetime.now(tz=timezone.utc) para garantizar
    # que la fecha y hora estén en la misma zona horaria.
    timestamp = db.Column(db.DateTime, default=datetime.now(tz=timezone.utc)) 

class Riego(db.Model):
    __tablename__ = 'riego'  # Asegúrate de que el nombre de la tabla coincide
    id = db.Column(db.Integer, primary_key=True)
    hora_inicio = db.Column(db.Time, nullable=False)
    hora_fin = db.Column(db.Time, nullable=False)
    dias = db.Column(db.String(255), nullable=False)
    timestamp = db.Column(db.DateTime, default=datetime.now(tz=timezone.utc))
