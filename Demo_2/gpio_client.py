import grpc
import gpio_service_pb2
import gpio_service_pb2_grpc
import time

def set_gpio_output(stub, pin, state):
    response = stub.SetOutput(gpio_service_pb2.SetOutputRequest(pin=pin, state=state))
    return response.response

def set_gpio_mode(stub, pin, mode):
    response = stub.ConfigurePin(gpio_service_pb2.ConfigurePinRequest(pin=pin, mode=mode))
    return response.response

def read_gpio_pin(stub, pin):
    response = stub.ReadState(gpio_service_pb2.ReadStateRequest(pin=pin))
    return response.response

def run_client():
    channel = grpc.insecure_channel('192.168.163.200:50051')
    stub = gpio_service_pb2_grpc.GPIOServiceStub(channel)

    # Example usage:
    pin_to_read = 15  # Pin to read state from
    pin_to_set = 26   # Pin to set based on the state

    # Configure GPIO pin 14 as input
    set_gpio_mode(stub, pin_to_read, gpio_service_pb2.ConfigurePinRequest.INPUT)

    # Configure GPIO pin 26 as output
    set_gpio_mode(stub, pin_to_set, gpio_service_pb2.ConfigurePinRequest.OUTPUT)

    # Toggle pin state based on pin 14 state
    while True:
        state = read_gpio_pin(stub, pin_to_read)  # Read state of pin 14
        set_gpio_output(stub, pin_to_set, state)  # Set pin 26 based on pin 14 state

if __name__ == '__main__':
    run_client()

