Block Diagram:

![image](https://github.com/user-attachments/assets/006f8f09-e52c-4168-bb0f-ff18eaa9c530)

Project Summary:

The project involves using an STM32 microcontroller to manage and monitor four street lights. These lights are connected via a 4-channel relay module, allowing precise control over each light's on/off state.

Wireless Communication is facilitated through a LoRa module, which enables long-range, low-power data transmission between the STM32 microcontroller and a Rugged Board. The system continuously transmits the status of each street light to the Rugged Board. This board stores the data in the cloud for remote monitoring and analysis.

The Rugged Board can issue two types of commands either "on" or "off" for each street light. These commands are relayed back to the STM32 microcontroller via the LoRa module, enabling real-time control over the street lights.

An LCD, connected to the STM32 via I2C, displays the current state of all four street lights. This user-friendly interface allows for easy monitoring and management of the lighting system.

Hardware Used and their Specification:

    • STM32 NUCLEO F446RE Microcontroller

Core
ARM® Cortex®-M4 CPU with DSP and FPU
Frequency: Up to 180 MHz
               Memory
Flash memory: 512 KB
SRAM: 128 KB (112 KB + 16 KB backup SRAM)

    •  4 channel relay

Control Signal
Input Voltage: Typically 3.3V to 5V DC
                Relay Output
Load Voltage: Up to 250V AC or 30V DC
Load Current: Typically up to 10A per channel   

    •  LCD – I2C module
                
                Display Type
Character LCD : 16x2
InterfaceI2C 
        Interface : Uses I2C protocol for communication,
                                         reducing the number of pins required

    •  LoRa module

Communication
Data Rate : LoRa modulation up to 300 kbps.
Power Requirements
Operating Voltage : 1.8V to 3.6V

Connection Diagram:

![image](https://github.com/user-attachments/assets/8d31a53f-5b2f-4002-90a7-4a6c5a227772)

Low Level Block Diagram:

![image](https://github.com/user-attachments/assets/f4f3daf5-95d6-409b-8d67-ad7ccd2cb021)

Sample Output:

![image](https://github.com/user-attachments/assets/f9cd699f-befb-4bb8-a288-9c616ee6f685)


