import serial
import time

class lights:
    def __init__(self):
        # Hard coded timing
        self.base_time = [31.084, 13, 22, 2, 12, 11, 32, 33, 2, 31, 19, 3, 41, 29, 3, 13, 3, 3, 32, 32, 0]
        self.static_time = [16, 4, 14, 10, 6, 13, 8, 21, 3, 3, 8, 9, 2, 13, 5, 7, 6, 5, 8, 13, 16]
        self.ser = serial.Serial('/dev/ttyUSB0') #Serial port of the arduino
        time.sleep(2)
        return
        
    # tells the arduino to play the static sequence
    def sendStatic(self):        
        self.ser.write(bytes('s', 'utf-8'))
        return
    
    # tells the arduino to play the blue sequence
    def sendBase(self):
        self.ser.write(bytes('b', 'utf-8'))
        return
        
    # tells the arduino to turn off the strip
    def sendToggle(self):
        self.ser.write(bytes('t', 'utf-8'))
        return
        
    # loop responsible for the timing
    def timeLights(self):
        print("timing lights")
        self.sendToggle()
        print("enabled lights")
        
        # time the lights using the delays from the array above
        for i in range(len(self.base_time)):
            self.sendBase()
            print("base running")
            time.sleep(self.base_time[i])

            self.sendStatic()
            print("static running") 
            time.sleep(self.static_time[i])
            
        # end the serial connection
        self.ser.close()
        return
        
    
