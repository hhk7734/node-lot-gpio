const lot = require("../index");

const uart = new lot.Uart( "/dev/ttyS1" );

uart.transmit(Buffer.from("hello world\r\n"));

setInterval(() => { 
    if( uart.available() )
    {
        uart.transmit( uart.receive() );
    }
},20)
