# ESP32 CAN Transceiver Firmware

This firmware allows the user to send data over WiFi to an ESP32 board, which is equipped with a CAN transceiver. The firmware processes the incoming packets and sends CAN messages from it to a CAN logger (PCAN) via two wires.

## Requirements
To use this firmware, you will need the following:

- An ESP32 board with WiFi connectivity and a CAN transceiver module.
- Arduino IDE with the ESP32 libraries installed.
- A CAN logger, such as PCAN, to receive and log the CAN messages.

## Installation

- one this Git repository to your local machine.
- Open the Arduino IDE and import the firmware sketch (esp32_can_transceiver_firmware.ino) from the cloned repository.
- Connect your ESP32 board to your computer via USB and select the appropriate board and port settings in the Arduino IDE.
- Compile and upload the firmware sketch to your ESP32 board.
Usage
- Once the firmware is uploaded to your ESP32 board, it will automatically connect to a WiFi network.
- The firmware will display the IP address and port number of the web server on the Serial Monitor. Note down this information as it will be needed to access the web server.
- Open a web browser and navigate to the IP address and port number of the web server.
- Enter a message in the input text box on the webpage. The message should be no longer than 32 characters.
- Click the "Send" button to send the message to the ESP32 board.
- The firmware will convert the message into a CAN message and send it to the CAN logger.

## Configuration

The following parameters can be configured in the firmware sketch:

- WIFI_SSID: The SSID of the WiFi network to connect to.
- WIFI_PASSWORD: The password of the WiFi network.
- CAN_TX_PIN: The GPIO pin used for transmitting CAN messages.
- CAN_RX_PIN: The GPIO pin used for receiving CAN messages.

## Troubleshooting

- If you encounter any issues with the firmware, try resetting the ESP32 board and/or restarting the CAN logger.
- Check that the board and port settings in the Arduino IDE are correct.
- Check that the CAN transceiver module is properly connected to the ESP32 board.