# ESP32 Environmental Sensor System

\------------------------------------------------------------------------

##### Quick Start

git clone https://github.com/hreide/sensor-node

cd sensor-node

pip install -r requirements.txt

python logger/logger.py --port /dev/ttyUSB0 --baud 115200 -out data.csv



cd firmware

idf.py flash

\------------------------------------------------------------------------

###### System Overview

BME280				Temperature, Humidity, Pressure

BH1750				Ambient Light (Lux)

Capacitive Moisture Sensor	Soil Moisture (ADC)

\------------------------------------------------------------------------

###### Repo Structure

/firmware	ESP-32S firmware

/logger		Python CSV Logger

/hardware	Schematics, PCB, diagrams, photos

/docs		Block Diagrams, notes, etc

\------------------------------------------------------------------------

###### Description

A compact embedded sensing system, built around an affordable and expandable ESP32 board to monitor local plant/environment conditions: soil moisture, ambient light, temperature, humidity, and pressure. 



The project will move from prototype to data logging and analysis for integration with another simple home automation project.

The project utilizes simple sensing within an embedded firmware structure, serial data logging, and a python workflow for collecting  measurements.

\------------------------------------------------------------------------

