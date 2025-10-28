 # Read temperature from DS18B20(s) and publish to MQTT broker. 

Starting from the template <https://github.com/HankB/ESP32-ESP-IDF-CLI-start>

## Useful links

* <https://www.analog.com/media/en/technical-documentation/data-sheets/ds18b20.pdf> Data sheet
* <https://components.espressif.com/components/espressif/ds18b20/versions/0.2.0/readme>

Leaving the links to Espressif guides as a convenience.

* <https://docs.espressif.com/projects/esp-idf/en/stable/esp32/index.html> Programming guide
* <https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/index.html> API reference
* <https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/index.html> API guide

## Motivation

Produce code for an ESP32 that reads one or more DS18B20 temperature sensors and publishes them to an MQTT broker formatted as JSON.

## Status

* Resetting the project.
* Template code works.

## Build

```text
cd project
. ~/esp/esp-idf/export.sh # Assuming Espressif tools installed at ~/esp
idf.py set-target # optional if other than esp32
# Connect ESP
idf.py build flash monitor
```

## Plans

* Build the template and confirm that it works.
* Connect a DS18B20 sensor and add the DS18B20 driver.

### DS18B20 connections for `esp32`

* sensor to ESP
* Vcc to 3V3
* GND to GND
* DATA to D4
* 2.6KΩ resistor from Vcc to DATA. (4.7KΩ recommended)

```text
idf.py add-dependency "espressif/ds18b20^0.2.0" 
```

## Errata

Note: SSID and password does not come from example config but rather the `secrets.h` file which the user must provide. A template looks like:

```text
#define SSID "ssid"
#define  PWD "password"

#define sntp_server "serve_name|server_IP"
#define broker_list "mqtt://hostname:1883" 

```

All project files moved to `.../project` so the viewer need not scroll down so much to find the README.