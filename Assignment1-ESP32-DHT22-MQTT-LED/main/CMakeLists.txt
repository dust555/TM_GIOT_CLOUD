set(COMPONENT_SRCS "main.c"
                    "./wifi/wifi.c"
                    "./time/time.c"
                    "./temperature/temperature.c"
                    "./temperature/dht.c"
                    "./mqtt/mqtt.c"
                    "./led/led.c")
set(COMPONENT_ADD_INCLUDEDIRS "." 
                                "../components/helloworld")

register_component()