# -*- coding: utf-8 -*-
"""
Created on Fri Oct 13 11:56:55 2023

@author: percy
"""

from socket import *

serverPort = 23450

serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(("", serverPort))


print("Server operational...")

count_votes, clientAddress = serverSocket.recvfrom(2048)
end = count_votes.decode()

cand = []


for x in range(int(end)):
    vote, clientAddress = serverSocket.recvfrom(2048)
    name = vote.decode()
    cand.append(name)
        
    message = "Vote Successful"
    serverSocket.sendto(message.encode('utf-8'), clientAddress)
    

x= cand.count("Daniel")
y= cand.count("JaneD")
z= cand.count("JohnD")

if ((x==y and x!=z)or (x==z and x!=y)):
    print("There was a two way tie")
    result1 = "There was a two way tie"
    serverSocket.sendto(bytes(str(result1), "utf-8"), clientAddress)
    
if x==y and y==z:
    print("There was a three way tie")
    result1= "There was a three way tie"
    serverSocket.sendto(bytes(str(result1), "utf-8"), clientAddress)

most= max(x,y,z)
if most == x:
    winner = "Daniel"
if most == y :
    winner = "JaneD"
if most == z:
    winner = "JohnD"

if x != y and x != z and y != z: 
    result2 = "Daniel got " + str(x) + " votes JaneD got " + str(y) + " votes JohnD got " + str(z) + " votes so " +str(winner) + " wins"
    print(result2)
    serverSocket.sendto(bytes(str(result2), "utf-8"), clientAddress)


    
    



    
    
    
    


    
        

    
    
    
    
    



    



