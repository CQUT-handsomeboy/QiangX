import network
from machine import UART,Pin

class qxWifi(object):
    def __init__(self,ssid,password):
        self.ssid = ssid
        self.password = password
        self.ip_address = "0.0.0.0"
        self.sta_if = network.WLAN(network.STA_IF)

    def connect_for_while(self,forget=False):
        if (forget) or (not self.isconnected):
            self.sta_if.active(False)
            self.sta_if.active(True)
            self.sta_if.connect(self.ssid, self.password)
            while not self.sta_if.isconnected():
                pass
        else:
            self.sta_if.active(True)
        self.ip_address = self.sta_if.ifconfig()[0]

    @property
    def isconnected(self):
        return self.sta_if.isconnected()

class qxUART(object):
    def __init__(self,txd:int,rxd:int):
        self.uart_port = next(qxUART._g())
        self._uart = UART(self.uart_port,baudrate=115200,tx=Pin(txd),rx=Pin(rxd))

    def send_data(self,data:str):
        self._uart.write(data)

    def receice_data_for_while(callback_func):
        while True:
            if self._uart.any():
                data = uart.read()
                callback_func(data.decode('utf-8'))

    @staticmethod
    def _g() -> int:
        for i in range(1,3):
            yield i


if __name__ == "__main__":
    my_uart = qxUART(1,2)
    my_uart.send_data("Hello")
