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

module.exports = router;
