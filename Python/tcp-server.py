import time
import socket
import sys
import datetime
port = None

tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   
if len(sys.argv) > 1:  
    port = sys.argv[1]
else:
    port = input("Enter port: ")
tcp.bind(('', int(port)))
tcp.listen(0)
print("Listening on port " + str(port))
while(True):
    conn, addr = tcp.accept()
    print("Client connected, IP: " + str(addr[0]) + ":" + str(addr[1]))
    while(True):
        data = conn.recv(1024)
        msg = data.decode('utf-8')
        if not data:
            print("Client disconnected")
            break
        if len(msg) > 0:
            received = "Message received!"
            conn.send(str.encode(received))
        if msg == "/exitserver":
            print("Server exiting...")
            time.sleep(0.5)
            tcp.close()
            sys.exit(0)
        print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") + " Message from " + addr[0] + ": " + data.decode('utf-8'))
