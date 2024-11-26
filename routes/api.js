const express = require('express');
const router = express.Router();
const dataController = require('../controllers/dataController');

// Ruta para recibir datos del dispositivo
router.post('/data', dataController.receiveData);

// Ruta para enviar comandos al dispositivo
router.post('/control', dataController.sendCommand);

// Ruta para verificar el estado
router.get('/status', (req, res) => {
  res.json({ status: 'Servidor funcionando correctamente' }); // usando postman se verifico que esta correcto la ruta
});
//ruta que recibe de el sensor
router.post('/sensores', (req, res) => {
  const { temperatura, humedad } = req.body;

  if (temperatura === undefined || humedad === undefined) {
    return res.status(400).json({ error: 'Faltan datos en la solicitud' });
  }

  console.log(`Temperatura: ${temperatura}, Humedad: ${humedad}`);
  res.status(200).json({ message: 'Datos recibidos correctamente' });
});

router.get('/sensores', (req, res) => {
  res.status(200).json({ message: 'Ruta activa para pruebas' });
});



module.exports = router;
