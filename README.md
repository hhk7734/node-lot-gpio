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
curl -sL https://deb.nodesource.com/setup_12.x | sudo -E bash - &&\
sudo apt-get install -y nodejs
```

```bash
mkdir project &&\
cd project &&\
npm init -y
```

```bash
npm install lot-gpio
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
