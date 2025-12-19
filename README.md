# Conductivity Meter (Embedded Systems Project)

## Overview
An embedded conductivity meter designed to measure water conductivity/TDS using an AC excitation method and microcontroller-based signal processing.

## Motivation
This project was developed to explore practical sensor design, analog signal conditioning, and embedded firmware development for real-world water quality monitoring applications.

## System Design
- AC excitation signal applied to probe electrodes
- Analog signal conditioning and amplification
- ADC sampling and digital processing
- Conductivity calculation and calibration

## Hardware
- Seeed Studio XIAO SAMD21 Microcontroller (Arduino-compatible)
- TDS Water Conductivity Sensor Conductivity probe
- LCD 20x4 Display with I2C Interface

## Firmware
- Analog signal sampling via ADC
- RMS/average voltage calculation
- Calibration curve application

## Results
- Successfully measured relative conductivity changes
- Calibration performed using known reference solutions
- Repeatable measurements under controlled conditions

## Files
- Firmware: `ConductivityMeter/ConductivityMeter.ino`

## Future Improvements
- Temperature compensation
- Use a more power efficient and powerful microchip (ie STM32L)
- Improved probe geometry
- Digital filtering
- Enclosure and waterproofing