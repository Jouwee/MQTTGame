var mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://localhost:1883')

var WebSocketServer = require('websocket').server;
var http = require('http');

client.subscribe("/teste")

var server = http.createServer();
server.listen(1337);

wsServer = new WebSocketServer({
    httpServer: server
});

wsServer.on('request', function(request) {
    var connection = request.accept(null, request.origin);
    connection.on('message', function(message) {
    });

    client.on('message', function (topic, message) {
        console.log(message.toString())
        connection.sendUTF(message.toString());        
    })
    connection.on('close', function(connection) {
    });
});