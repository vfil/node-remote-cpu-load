const cpuLoadAddon = require('./build/Release/cpuload');

module.exports = function() {
    return cpuLoadAddon.retrieve();
};
