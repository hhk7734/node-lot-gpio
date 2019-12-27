# node-lot-gpio

## Installation

```bash
sudo add-apt-repository -y ppa:loliot/ppa &&\
sudo apt install lot
```

```bash
sudo lot install
```

```bash
npm install -g lot-gpio
```

## Blink example

```javascript
const lot = require("lot-gpio");

const LED_PIN = 7;

lot.set_pin_mode(LED_PIN, "OUTPUT");

let status = "HIGH";

setInterval(() => {
    if (status == "HIGH") {
        lot.digital_write(LED_PIN, "LOW");
        status = "LOW";
    } else {
        lot.digital_write(LED_PIN, "HIGH");
        status = "HIGH";
    }
}, 500);
```
