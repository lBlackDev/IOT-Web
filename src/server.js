const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
require('dotenv').config();
const { WebSocketServer } = require('ws');
const { addClient, removeClient } = require('./websocket');



const app = express();
const port = process.env.PORT || 3000;

// Middlewares
app.use(bodyParser.json());
app.use(cors());

// Rutas
const apiRoutes = require('../routes/api');
app.use('/api', apiRoutes);

// Servir archivos estáticos
app.use(express.static('public'));

// Iniciar servidor HTTP
const server = app.listen(port, () => {
  console.log(`Servidor corriendo en http://localhost:${port}`);
});

// Crear servidor WebSocket
const wss = new WebSocketServer({ server });

wss.on('connection', (ws) => {
  console.log('Cliente conectado vía WebSocket');
  addClient(ws);

  ws.on('message', (message) => {
    console.log('Mensaje recibido del cliente:', message);
  });

  ws.on('close', () => {
    console.log('Cliente desconectado');
    removeClient(ws);
  });
});
