/*jslint node: true */
"use strict";

var serialport = require('serialport'),
    shelljs = require('shelljs');

var serial = new serialport.SerialPort("COM3", {
    baudrate: 9600,
    parser: serialport.parsers.readline("\n")
});

serial.on('data', function (data) {
    var speed = parseFloat(data);
    var limit = speed * 800;
    console.log(limit);
    shelljs.exec("sudo", "wondershaper", "eth0", limit, limit);
});

serial.on('close', function () {
    shelljs.exec("sudo", "wondershaper", "remove", "eth0");
});