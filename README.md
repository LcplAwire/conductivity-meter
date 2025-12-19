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
- Microcontroller (Arduino-compatible)
- Conductivity probe (custom electrodes)
- Op-amp signal conditioning stage
- Passive components (resistors, capacitors)

## Firmware
- Analog signal sampling via ADC
- RMS/average voltage calculation
- Calibration curve application
- Serial output for debugging and data logging

## Results
- Successfully measured relative conductivity changes
- Calibration performed using known reference solutions
- Repeatable measurements under controlled conditions

## Files
- Firmware: `src/ConductivityMeter.ino`
- Documentation: `docs/Conductivity_Meter_Report.pdf`
- Calibration data: `data/calibration_data.csv`

## Future Improvements
- Temperature compensation
- Improved probe geometry
- Digital filtering
- Enclosure and waterproofing