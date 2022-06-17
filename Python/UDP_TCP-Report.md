Lê Gia Hiển BI11-079
# Report for UDP and TCP exercises
## UDP Server
```
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
```
## UDP Client
```
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
```
## Connecting to other student's server 
### Client
```
hienthecat@UbuntuV:~/Desktop/Network_Programming/netprog2022/Python$ python3 udp-client.py
Enter IP: 10.10.15.145
Enter port: 1234
Enter message: hello
Sending message to 10.10.15.145:1234
Enter message: 
```
### Server
```
15:54:25 server receive from ('10.10.14.238', 60221) message hello
```
## ARP traffic when sending to new computer
![](https://raw.githubusercontent.com/hienthecat/netprog2022/main/Python/ARP.png)
## UDP traffic
![](https://raw.githubusercontent.com/hienthecat/netprog2022/main/Python/UDP_Packages.png)
## Reading UDP traffic
![](https://raw.githubusercontent.com/hienthecat/netprog2022/main/Python/UDP_Read.png)
### -> UDP traffic can be read because the connection is not encrypted!
## The types of cnx and addr are:
### cnx: socket
### addr: socket._RetAddress
## TCP listen test
### Server
```
hienthecat@UbuntuVPS:~/netprog2022/Python$ python3
Python 3.8.10 (default, Mar 15 2022, 12:22:08) 
[GCC 9.4.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import socket 
>>> tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   
>>> tcp.bind(('', 8784))
>>> tcp.listen(0)
>>> conn, addr = tcp.accept()
>>> ...
```
### Netstat
![](https://raw.githubusercontent.com/hienthecat/netprog2022/main/Python/TCP_Listen.png)

