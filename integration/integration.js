const net = require('net');
const tcpServer = require('../tcp-server.js');

describe('module integration tests', function() {
    it('should stream cpu load through tcp socket', function(done) {
        tcpServer().then((address) => {
            console.log(address);
            const client = net.connect(address, () => {
                console.log('client connected.');
            });
            //done();
        });
    });
});
