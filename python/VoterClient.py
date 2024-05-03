# -*- coding: utf-8 -*-
"""
Created on Fri Oct 13 10:16:32 2023

@author: percy

"""
from socket import *

serverName = "localhost"
serverPort = 23450

clientSocket = socket(AF_INET, SOCK_DGRAM)

print("Client is operational...\n")

file= open("votes.txt", "r")

candList = []
count_votes = 0

for i in file:
    name = i
    candList.append(name.strip())
    count_votes += 1

clientSocket.sendto(bytes(str(count_votes), "utf-8"), (serverName, serverPort))
    
for x in range (count_votes):
    vote = candList[x]
    clientSocket.sendto(bytes(vote, "utf-8"),(serverName, serverPort))
    message, serverAddress = clientSocket.recvfrom(2048)
    print(message.decode())
    
print ("End of voting...")

results, serverAddress = clientSocket.recvfrom(2048)
results= results.decode()
print(results)

file.close()


    
    




    
