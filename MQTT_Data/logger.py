import paho.mqtt.client as mqttClient
from datetime import datetime

#file with credentials
import credentials as cr
#MQTT - Server credentials from the file above
broker_address = cr.broker_address
port = cr.port
user = cr.user
password = cr.password

topic1 = "moisture"
topic2 = "voltage"
data_file = "./data.csv"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        client.subscribe(topic1)
        client.subscribe(topic2)
        print("Connected")
        with open(data_file,'a+') as f:
            f.write(str(datetime.now()) + ";Connected;\n")
    else:
        print("Connection failed")
        with open(data_file,'a+') as f:
            f.write(str(datetime.now()) + ";Connection failed;\n")

def on_disconnect(client, userdata, rc):
    print("Connection lost")
    with open(data_file,'a+') as f:
        f.write(str(datetime.now()) + ";Connection lost;\n")

def on_message(client, userdata, message):
    print("Message received")
    text = '"' + str(datetime.now()) + '";"' + str(message.topic)  + '";"' + str(message.payload) + '";' + str(message.retain) + ';\n'
    with open(data_file,'a+') as f:
        f.write(text)

client = mqttClient.Client("Python")
client.username_pw_set(user, password=password)
client.on_connect= on_connect
client.on_message= on_message
client.on_disconnect= on_disconnect
client.connect(broker_address, port, 60)
client.loop_forever()
