let connectedClients = [];

// Agregar cliente a la lista
function addClient(ws) {
  connectedClients.push(ws);
}

// Remover cliente de la lista
function removeClient(ws) {
  connectedClients = connectedClients.filter(client => client !== ws);
}

// Enviar datos a todos los clientes conectados
function broadcastData(data) {
  console.log('Enviando datos a los clientes WebSocket:', data);
  connectedClients.forEach(client => {
    if (client.readyState === 1) { // WebSocket.OPEN
      client.send(JSON.stringify(data));
    }
  });
}

module.exports = { addClient, removeClient, broadcastData };
