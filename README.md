# PlantWatering
Automatic Plant Watering and collecting soil moisture data.

If you fork this repository, I strongly recommend to execute this commands (below) locally in order to prevent from leaking your credentials:

<code>git update-index --assume-unchanged ./PlantWatering/PlantWatering/credentials.hpp</code>

<code>git update-index --assume-unchanged ./PlantWatering/MQTT_Data/credentials.py</code>

This will allow you to only change credentials locally and do not send them to remote ropository.

This is my hobby project. 

This device allow to water single plant and to collect soil moisture data.

<br/><b><i>Structure of folders:</i></b>
<br/><b>CircuitDiagram</b> - circuit diagram with the list of necessary electronic components
<br/><b>PlantWatering</b> - program for microcontroller
<br/><b>MQTT_Data</b> - simple MQTT logger written in python
<br/><b>photo</b> - photo and video of the device

Device checks soil moisture once an hour and will pour approximately 300 ml of water when soil moisture below 20%.

In order to collect moisture data you need some MQTT server, either set up locally or some remote service. Or you can just delete this part of a code and use it without collecting soil moisture data.

<b><i>MQTT topics:</i></b>
<br/><b>voltage</b> - voltage of battery
<br/><b>moisture</b> - moisture level in percent
<br/><b>water</b> - two values available (1 - plan was watered, 0 - plant was not watered)
