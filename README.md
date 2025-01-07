# Dusk/Dawn Interactive Horror Experience Rift Room Code

The main programs are lights.py and Rift.ino

lights.py is used by the other scripts and sends characters over serial to the arduino

Rift.ino is on the Arduino. It controls the light sequences and defines the characters used for communication

The other python scripts import lights.py and send individual characters with a single script. This was for ease of use in an SSH terminal session.
