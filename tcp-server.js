const net = require('net');

const cpuLoad = require('./js-cpu-load.js');


module.exports = function() {
    const options = {
        allowHalfOpen: false,
        pauseOnConnect: false
    };

    const server = net.createServer(options, (c) => {
        setInterval(() => {
            c.write(cpuLoad());
        }, 1000);
    });

    return new Promise((resolve, reject) => {
        server.listen(() => {
            resolve(server.address());
        });
    });
};
