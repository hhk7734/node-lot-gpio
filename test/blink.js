const lot = require("../index");

let pin = 13;

if (process.argv.length > 2) {
    pin = Number(process.argv[2]);
}

led = new lot.Gpio(pin);
led.mode(lot.DOUT);

setInterval(() => {
    led.toggle();
}, 200);
