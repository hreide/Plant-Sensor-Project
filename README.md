<p align="center">
  <img src="docs/banner.png" width="100%" alt="ESP32 Environmental Sensor System Banner">
</p>
# ESP32 Environmental Sensor System

\------------------------------------------------------------------------

A compact embedded sensing system, built around an affordable and expandable ESP32 board to monitor local plant/environment conditions: soil moisture, ambient light, temperature, humidity, and pressure. 

\------------------------------------------------------------------------

##### Quick Start

git clone https://github.com/hreide/Plant-Sensor-Project
cd sensor-node

pip install -r requirements.txt
python python/logger.py --port /dev/ttyUSB0 --baud 115200

cd firmware
idf.py flash

\------------------------------------------------------------------------

###### System Overview

BME280				Temperature, Humidity, Pressure

BH1750				Ambient Light (Lux)

Capacitive Moisture Sensor	Soil Moisture (ADC)

\------------------------------------------------------------------------

###### Repo Structure

/firmware	    ESP-32S firmware

/python		    Python CSV Logger

/hardware	    Schematics, PCB, diagrams, photos

/docs		      Block diagrams, notes, etc

\------------------------------------------------------------------------

###### Future of the Project

The project will move from prototype to data logging and analysis for integration with my other home-automation project.

The project utilizes simple sensing within an embedded firmware structure, serial data logging, and a python workflow for collecting  measurements.

\------------------------------------------------------------------------

