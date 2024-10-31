import grpc
import gpio_service_pb2
import gpio_service_pb2_grpc
import unittest


stub = ''

high = 1
low = 0

def set_gpio_output( pin, state):
    response = stub.SetOutput(gpio_service_pb2.SetOutputRequest(pin=pin, state=state))
    return response.response

def set_gpio_mode( pin, mode):
    response = stub.ConfigurePin(gpio_service_pb2.ConfigurePinRequest(pin=pin, mode=mode))
    return response.response

def read_gpio_pin( pin):
    response = stub.ReadState(gpio_service_pb2.ReadStateRequest(pin=pin))
    return response.response

def run_client():
    global stub
    channel = grpc.insecure_channel('192.168.163.200:50051')
    stub = gpio_service_pb2_grpc.GPIOServiceStub(channel)



class TestGPIO(unittest.TestCase):
    
    def test_gpio_26_set_low(self):
        run_client()
        set_gpio_mode(26, gpio_service_pb2.ConfigurePinRequest.OUTPUT)
        self.assertEqual(set_gpio_output(26, low), True)

    def test_gpio_26_set_high(self):
        run_client()
        set_gpio_mode(26, gpio_service_pb2.ConfigurePinRequest.OUTPUT)
        self.assertEqual(set_gpio_output(26, high), True)

   
############################ GET PIN TEST CASES ####################

    def test_gpio_15_get_high(self):
        run_client()
        set_gpio_mode(15, gpio_service_pb2.ConfigurePinRequest.INPUT)
        self.assertEqual(read_gpio_pin(15), high)


    def test_gpio_15_get_low(self):
        run_client()
        set_gpio_mode(15, gpio_service_pb2.ConfigurePinRequest.INPUT)
        self.assertEqual(read_gpio_pin(15), low)







if __name__ == '__main__':
    run_client()
    unittest.main()

