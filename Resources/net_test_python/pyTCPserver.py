import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', 12000)
print ('starting up on %s port %s' % server_address)
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)



while True:
    # Wait for a connection
    print ('waiting for a connection')
    connection, client_address = sock.accept()

    try:
        print ('connection from', client_address)

        # Receive the data in small chunks and retransmit it
        while True:
            data = connection.recv(100)
            print ('received "%s"' % data)
            if data:
                print ('sending data back to the client')
                connection.sendall(data)
            else:
                print ('no more data from', client_address)
                break

    except:
        print('failure')

    finally:
        # Clean up the connection
        connection.close()

		
# Some notes here on program flow when waiting for commands from program
#
#(states and flow)
#	-disconnected
#		-wait for TCP connection
#			-verify connection is authentic
#			-connected
#
#	-connected and authorized
#		-wait for command
#			-set observe
#			-set update
#			-set manual
#			-close conn
#			-request logs
#		
#