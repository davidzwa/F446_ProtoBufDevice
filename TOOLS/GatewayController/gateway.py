import serial


class Gateway:
    def __init__(self, portname):
        self.ser = self.openCOM(portname)
        print(f'Connected to gateway on {portname}')

        self.serialBuffer = []
        self.delimiter = b'\n\r'

    def openCOM(self, portname):
        return serial.Serial(
            port=portname,
            baudrate=921600,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS
        )

    def readLine(self):
        return self.ser.read_until(self.delimiter)


