# Room_Detection_with_BLE
The code base is segmented into three directories: Hardware, Server, Frontend.

## Hardware
- Run on Arduino IDE
- Contains code to set up the transmitters and scanners on the ESP32 boards using Bluetooth and Wifi Libraries.

## Server
- Run using Python Flask
- Server collects data from the ESP32 boards, processes it, classifies it and communicates the resuls with the frontend.


## Frontend
- Run using ReactJS
- A simple UI depicts the room each data point gets classified to and the classified room after batching has been performed.

