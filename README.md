#Dusk/Dawn Interactive Horror Experience Rift Room Code

The main programs are lights.py and Rift.ino

lights.py is used by the other programs and it sends characters over serial to the arduino

Rift.ino actually controls the light sequences and defines the characters used for communication

The other python scripts just import lights.py and send individual characters with just a script. This was for ease of use in an SSH terminal session.
