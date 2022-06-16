from datetime import datetime
import socket
import sys
import datetime
port = None
if len(sys.argv) > 1:
    port = int(sys.argv[1])
else:
    port = int(input("Enter port: "))
if port == None:
    print("Invalid port!")
    sys.exit(1)
UDPSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
UDPSocket.bind(('', port))
print("Listening on port " + str(port))
while True:
    data, addr = UDPSocket.recvfrom(1024)
    recvmsg = data.decode('utf-8')
    if recvmsg == "/exitserver":
        print("Server exiting...")
        sys.exit(0)
    print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") + " Message from " + addr[0] + ":" + data.decode('utf-8'))
