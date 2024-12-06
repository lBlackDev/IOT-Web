from datetime import timedelta
class Config:
    SQLALCHEMY_DATABASE_URI = 'mysql://root:2154@localhost/sensordata'
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    TIMEZONE = 'America/Santiago'
