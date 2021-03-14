import json
import boto3

led_topic = "<YOUR_LED_TOPIC>"
temp = 22.00

client = boto3.client('iot-data', region_name='eu-west-1')

def lambda_handler(event, context):
    if float(event["temperature"]) > temp:
        client.publish(topic=led_topic, qos=1, payload="1") 
    else:
        client.publish(topic=led_topic, qos=1, payload="0") 
    return {
        'statusCode': 200,
        'body': json.dumps('control LED')
    }