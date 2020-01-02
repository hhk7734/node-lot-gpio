const lot = require("../lot-gpio");

let max_pin = 40;

if (process.argv.length > 2) {
    max_pin = Number(process.argv[2]);
}

function pad(n, width, fill = "0") {
    n = n + "";
    return n.length >= width
        ? n
        : new Array(width - n.length + 1).join(fill) + n;
}

for (let i = 1; i <= max_pin; ++i) {
    let msg = pad(i, 3) + ": ";
    if (lot.get_lot_pin_available(i) != "UNUSED") {
        msg += pad(lot.get_pin_mode(i), 4, " ");
        // msg+= " " + lot.get_pin_drive( i );
    } else {
        msg += "    ";
    }
    if (i % 2 == 1) {
        msg += "\t";
    } else {
        msg += "\n";
    }

    process.stdout.write(msg);
}
