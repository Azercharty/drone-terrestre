import paho.mqtt.client as mqtt
import time
broker="192.168.1.5"
port=1883

def on_log(client, userdata , level , buf):
    print(buf)
def on_connect(client, userdata, flags , rc):
    if rc==0:
        client.connected_flag=True #set flag
        print("connected OK")
    else:
        print("Bad connection Returned code=",rc)
        client.loop_stop()
def on_disconnect(client, userdata, rc):
    print("client disconnected ok ")
def on_publish(client, userdata, mid ):
    print("In on_pub callback mid= " , mid)

mqtt.Client.connected_flag=False #create flag in class
client= mqtt.Client("RobotCharles")
client.on_log=on_log
client.on_connect=on_connect
client.on_disconnect=on_disconnect
client.on_publish=on_publish
client.connect(broker,port)
client.loop_start()
while not client.connected_flag: #wait in loop
    print("in wait loop")
    time.sleep(1)
time.sleep(3)
print("publishing")
ret=client.publish("RobotCharles","REGARDE C'EST TOUT DOUX !",0) #publish
print ("published return=",ret)
time.sleep(3)

