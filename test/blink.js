const lot = require("../lot-gpio");

let pin = 13;

if (process.argv.length > 2) {
    pin = Number(process.argv[2]);
}

try {
    lot.set_pin_mode(pin, "OUT");
    setInterval(() => {
        if (lot.digital_read(pin) == "HIGH") {
            lot.digital_write(pin, "LOW");
        } else {
            lot.digital_write(pin, "HIGH");
        }
    }, 300);
} catch (exception) {
    console.log(exception);
}
