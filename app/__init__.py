from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy
from flask_cors import CORS

db = SQLAlchemy()

def create_app():
    app = Flask(__name__, template_folder='templates')
    app.config.from_object('config.Config')

    CORS(app)  # Habilita CORS para toda la aplicación

    db.init_app(app)

    with app.app_context():
        from . import routes, models
        db.create_all()

    return app
