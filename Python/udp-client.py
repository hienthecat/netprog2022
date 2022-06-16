import socket
import sys
ip = None
port = None
userinput = None
msg = None
UDPSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
if len(sys.argv) > 1:
    ip = sys.argv[1]
else:
    ip = input("Enter IP: ")
if len(sys.argv) > 2:
    port = int(sys.argv[2])
else:
    port = int(input("Enter port: "))
if ip == None or port == None:
    print("Invalid IP or port")
    sys.exit(1)
if len(sys.argv) > 3:
    userinput = sys.argv[3]
else:
    while(True):
        userinput = input("Enter message: ")
        if userinput == "/exit":
            print("Exiting...")
            sys.exit(0)
        msg = str.encode(userinput)
        print("Sending message to " + ip + ":" + str(port))
        UDPSocket.sendto(msg, (ip, port))
        
        
