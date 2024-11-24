const { broadcastData } = require('../src/websocket'); // Asegúrate de que la ruta sea correcta

let latestData = {}; // Variable para almacenar los últimos datos recibidos

// Manejar datos enviados por el dispositivo
exports.receiveData = (req, res) => {
  const data = req.body; // Datos enviados por el dispositivo
  console.log('Datos recibidos:', data);
  latestData = data; // Guardar los datos
  broadcastData(data); // Enviar los datos a los clientes conectados
  res.status(200).json({ message: 'Datos recibidos correctamente' });
};

// Enviar comandos al dispositivo
exports.sendCommand = (req, res) => {
  const command = req.body.command; // Comando enviado desde el frontend
  console.log('Comando enviado:', command);
  res.status(200).json({ message: 'Comando enviado correctamente' });
};
