RFID


Wiki:

## SPI library

This library allows you to communicate with SPI devices, with the Arduino as the master device.
A Brief Introduction to the Serial Peripheral Interface (SPI)

Serial Peripheral Interface (SPI) is a synchronous serial data protocol used by microcontrollers for communicating with one or more peripheral devices quickly over short distances. It can also be used for communication between two microcontrollers.

With an SPI connection there is always one master device (usually a microcontroller) which controls the peripheral devices. Typically there are three lines common to all the devices:

    MISO (Master In Slave Out) - The Slave line for sending data to the master,
    MOSI (Master Out Slave In) - The Master line for sending data to the peripherals,
    SCK (Serial Clock) - The clock pulses which synchronize data transmission generated by the master 
