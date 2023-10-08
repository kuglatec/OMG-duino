# OMG-duino
Make your own budget OMG-plug

# Hardware

You should use a arduino micro or pro-micro to emulate the keyboard input and a NodeMCU ESP8266 board.

You also need 3 cables, which you will use to connect the GND pin of both and the D1 of the ESP with the 3 of the pro micro and the D2 with 2.

The cables are necessary for the I2C databus to work.

2 micro-USB cables are also required to give the boards the required power.

# Setup

Install the ESP boards into your IDE and compile the slave code to the pro-micro and the master code to the ESP

# Usage 

Plug the slave into your target computer.

The master can also get his power from this, but you can also use some sort of powerbank for this.

Connect your phone to the wifi AP which should be called something like ESP-FCA3F2 and visit http://192.168.1.1 to access the web interface.

You can type your desired command into the text bar and click execute to output them onto the USB port.

To run commands, just press the RUN button in the interface to open the RUN menu on windows devices.

# Credits

Thanks to HEINZGUENTER for his awesome ESP8266-captivePortal project, which has helped me building this.


# WARNING
This software is made for educational purposes only and comes with no warranty.
