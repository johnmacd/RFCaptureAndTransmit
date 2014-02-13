This is a simple Ardunio sketch to capture RF signals, and to re-transmit them.

It is intended for (or at least was written for) capturing the RF signals from RF controlled power sockets, but will work with any RF devices (Door bells, Alarm systems etc).

I am using a 433MHz reciever and transmiter from proto-pic

	http://proto-pic.co.uk/434mhz-rf-link-transmitter
	http://proto-pic.co.uk/433-mhz-rf-link-receiver-4800bps/

But should work with any.

The data out from the receiver is put into analog in A0 pin, and the data in to the transmiter is from digital pin 13.
I found my reciever worked best with a 3.3V power supply, and a pull down resistor.

Control messages are sent via Serial, to cause a capture or replay and to save/load the signals from EEPROM memory.
