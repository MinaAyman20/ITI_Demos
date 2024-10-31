import grpc
import gpio_service_pb2
import gpio_service_pb2_grpc
import RPi.GPIO as GPIO
from concurrent import futures

class GPIOServiceServicer(gpio_service_pb2_grpc.GPIOServiceServicer):
    def ReadState(self, request, context):
        # Read state of GPIO pin
        print("Recieved read state request from client")
        pin = request.pin
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(pin, GPIO.IN)
        state = GPIO.input(pin)
        return gpio_service_pb2.ReadStateResponse(response=state)

    def SetOutput(self, request, context):
        # Set output state of GPIO pin
        print("Recieved set output request from client")
        pin = request.pin
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, request.state)
        return gpio_service_pb2.SetOutputResponse(response=True)

    def ConfigurePin(self, request, context):
        # Configure pin mode
        print("Recieved pin configure request from client")
        pin = request.pin
        GPIO.setmode(GPIO.BCM)
        if request.mode == gpio_service_pb2.ConfigurePinRequest.INPUT:
            GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        elif request.mode == gpio_service_pb2.ConfigurePinRequest.OUTPUT:
            GPIO.setup(pin, GPIO.OUT)
        return gpio_service_pb2.ConfigurePinResponse(response=True)

    
def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    gpio_service_pb2_grpc.add_GPIOServiceServicer_to_server(GPIOServiceServicer(), server)
    server.add_insecure_port("[::]:50051")
    print("Started gpio server on port 50051")
    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
	GPIO.setwarnings(False)
	serve()
