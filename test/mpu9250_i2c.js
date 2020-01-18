const lot = require("../index");
const reg = require("./mpu9250_reg");

const i2c = new lot.I2c("/dev/i2c-2");

i2c.write_reg(
    reg.MPU9250_ADDRESS,
    reg.MPU9250_PWR_MGMT_1,
    Buffer.from([reg.MPU9250_H_RESET])
);

setTimeout(() => {
    i2c.write_reg(
        reg.MPU9250_ADDRESS,
        reg.MPU9250_PWR_MGMT_1,
        Buffer.from([reg.MPU9250_CLKSEL_PLL])
    );
    i2c.write_reg(
        reg.MPU9250_ADDRESS,
        reg.MPU9250_USER_CTRL,
        Buffer.from([reg.MPU9250_I2C_MST_EN])
    );

    setInterval(() => {
        let data = i2c.read_reg(
            reg.MPU9250_ADDRESS,
            reg.MPU9250_ACCEL_XOUT_H,
            6
        );

        /*
         * XH, XL, YH, YL, ZH, ZL
         * big-endian
         */
        let xyz = [];
        for (let i = 0; i < 3; ++i) {
            xyz[i] = data.readInt16BE(i * 2);
        }

        console.log(xyz);
    }, 300);
}, 100);
