import sys
import socket
ip = None
port = None 
userinput = None
tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
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
tcp.connect((ip, port))
if len(sys.argv) > 3:
    userinput = sys.argv[3]
else:
    while(True):
        userinput = input("Enter message: ")
        if userinput == "/exitserver":
            print("Server exiting...")
            tcp.send(str.encode(userinput))
            tcp.close()
            break
        if userinput == "/exit":
            print("Exiting...")
            tcp.close()
            sys.exit(0)
        print("Sending message to " + str(ip))
        tcp.send(str.encode(userinput))
        data = tcp.recv(1024)  
        print (data.decode())
