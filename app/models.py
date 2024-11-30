from . import db
from datetime import datetime

class SensorData(db.Model):
    __tablename__ = 'readings'  # Asegúrate de que el nombre de la tabla coincide
    id = db.Column(db.Integer, primary_key=True)
    temperature = db.Column(db.Float, nullable=False)
    humidity = db.Column(db.Float, nullable=False)
    timestamp = db.Column(db.DateTime, default=datetime.utcnow)
