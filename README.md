 # Read temperature from DS18B20(s) and publish to MQTT broker. 

Strting from the template <https://github.com/HankB/ESP32-ESP-IDF-CLI-start>

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

## Plans

* Build the template and confirm that it works.
* Connect a DS18B20 sensor and add the DS18B20 driver.

## Errata

Note: SSID and password does not come from example config but rather the `secrets.h` file which the user must provide.
