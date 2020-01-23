![license](https://img.shields.io/github/license/loliot/node-lot-gpio)
![node](https://img.shields.io/github/package-json/v/loliot/node-lot-gpio?sort=semver)
![language](https://img.shields.io/github/languages/top/loliot/node-lot-gpio)

# node-lot-gpio

## Installation

Ref: <a href="https://github.com/loliot/lot" target=_blank>https://github.com/loliot/lot</a>

```bash
sudo add-apt-repository -y ppa:loliot/ppa \
&& sudo apt install lot
```

```bash
sudo lot install cpp
```

```bash
curl -sL https://deb.nodesource.com/setup_12.x | sudo -E bash - \
&& sudo apt-get install -y nodejs
```

```bash
mkdir project \
&& cd project \
&& npm init -y
```

```bash
npm install lot-gpio
```

## Blink example

```javascript
const lot = require("lot-gpio");

let pin = 13;

if (process.argv.length > 2) {
    pin = Number(process.argv[2]);
}

const led = new lot.Gpio(pin);
led.mode(lot.DOUT);

setInterval(() => {
    led.toggle();
}, 200);
```
