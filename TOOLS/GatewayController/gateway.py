import serial


class Gateway(object):
    def __init__(self, portname, baudrate=921600):
        self.portname = portname
        self.baudrate = baudrate

    def openSerial(self):
        self.ser = serial.Serial(
            port=self.portname,
            baudrate=self.baudrate,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS
        )

        print(f'Connected to gateway on {self.portname}')

    def readLine(self):
        return self.ser.read_until()

    def write(self, buffer):
        return self.ser.write(buffer)
