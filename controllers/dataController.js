const { broadcastData } = require('../src/websocket'); // Asegúrate de que la ruta sea correcta

let latestData = {}; // Variable para almacenar los últimos datos recibidos

// Manejar datos enviados por el dispositivo
exports.receiveData = (req, res) => {
  const data = req.body; // Datos enviados por el dispositivo
  if (!data.temperatura || !data.humedad) {
    return res.status(400).json({ error: 'Datos incompletos' });
  }
  console.log('Datos recibidos del dispositivo:', data);
  latestData = data;
  broadcastData(data); // Retransmite datos vía WebSocket
  res.status(200).json({ message: 'Datos recibidos correctamente' });
};

// Enviar comandos al dispositivo
exports.sendCommand = (req, res) => {
  const command = req.body.command; // Comando enviado desde el frontend
  console.log('Comando enviado:', command);
  res.status(200).json({ message: 'Comando enviado correctamente' });
};
