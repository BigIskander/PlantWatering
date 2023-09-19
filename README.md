# PlantWatering
Automatic Plant Watering and collecting soil moisture data.

If you fork this repository, I strongly recommend to execute this commands (below) locally in order to prevent from leaking your credentials:

<code>git update-index --assume-unchanged ./PlantWatering/PlantWatering/credentials.hpp</code>

<code>git update-index --assume-unchanged ./PlantWatering/MQTT_Data/credentials.py</code>

This will allow you to only change credentials locally and do not send them to remote ropository.

This is my hobby project.

<br/><b><i>Structure of folders:</i></b>
<br/><b>CircuitDiagram</b> - circuit diagram with the list of necessary electronic components
<br/><b>PlantWatering</b> - program for microcontroller
<br/><b>MQTT_Data</b> - simple MQTT logger written in python
<br/><b>photo</b> - photo and video of the device
