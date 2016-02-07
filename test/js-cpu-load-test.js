const expect = require('chai').expect;
const sinon = require('sinon');
const cpuLoadAddon = require('../build/Release/cpuload');

describe("main module specs", function() {
    it("retrieve should get current cpu load", function() {
        const cpuLoad = require('../js-cpu-load.js');

        const addonStub = sinon.stub(cpuLoadAddon, 'retrieve').returns(0.5);

        expect(cpuLoad()).to.equal(0.5);
        expect(addonStub.calledOnce).to.equal(true);
    });
});
