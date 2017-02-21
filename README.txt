-------------------------------------------------------
EE 450 
Socket Programming
-------------------------------------------------------

Name: Akshay Kumar
Session: 4
USC ID: 3821-0240-34

-------------------------------------------------------

I. Work Done

In this socket programming project I have successfuly implemented 3 UDP servers, 1 TCP 
Server, 1 UDP client and 1 TCP client. There are 4 functions that coulde be performed: SUM, 
Sum of Square, Min and Max.

The entire project was first developed on Ubuntu and later shifted to nunki server. It worked
without any issues.

Based on the function called by the client, a corressponding index value is generated.
This index value ,numbers read from the nums.csv file and size of nums.csv file are appended
into an integer array. The size of integer array is taken as 1024 since the maximum numbers 
possible are 999. The complete array is sent to aws server over TCP connection.

At TCP server this array is read. The integer array is stored into three new arrays, each 
array consisting 1/3 of total numbers. Index value and size are stored in the beggining
of each array.

A seperate function for each UDP server is created. Connection to each UDP server is created
and each subarray is sent to UDP servers.

At the UDP servers, the received integer array is stored. Based on the index value, function
is performed. The result is returned back to AWS server over UDP.

AWS server receives the result from each of the UDP server. Based on the index value,
AWS server combines the result for all the numbers. This result is converted into a string. 
This string, that is the final answer is sent back to client over TCP connection. 

For AWS(TCP) serverA, serverB and serverC designated server port numbers are given as input in make file.
For AWS(UDP), the port number is hardcoded inside the aws.c file.

-------------------------------------------------------

II. File Structure

1. nums.csv 

File containing the numbers upon which the computation is needed to be done.

2. client.c

TCP client file reading numbers and passed function.

3. aws.c

AWS server server file acting as TCP server and UDP client. This receives numbers from 
client.c subdivides the number into 3 equal parts and forwards them to UDP server.

Later this AWS server receives the result from UDP server, combines the result and send it back to the client.

4. serverA.c, serverB.c, serverC.c

UDP servers receiving numbers from aws server, performing the computation and returning
the result to aws server.

5. makefile

file created to let make commands run

-------------------------------------------------------

III. Running the programs

To run the program follow the following steps:

1. write "make all" on the terminal. This would compile and create the executables for all the five 
files (client.c, aws.c, serverA.c, serverB.c, serverC.c)

2. run the execultables in the following order on five different terminals by typing:
   (a) make serverA
   (b) make serverB
   (b) make serverC
   (b) make aws

3. Run the client by typing "./client funcname"
   The funcname could be anything from {sum,sos,min,max}.

4. You should be able to see the results on the terminals.

-------------------------------------------------------

IV. Format of message exchanged

Client read the numbers from file. These are string. String is converted and stored
as integer array. Client sends integer array to AWS server. AWS serever also sends 
the integer array to UDP servers. UDP servers compute computations and return result in integer format to AWS.
Finally AWS converts final integer answer to string and return the resulting string to
client.

-------------------------------------------------------

V. Idiosyncrasy of the project

The following assumptions are required for proper functioning of the project:

1. The maximum amount of numbers in nums.csv sould be 999.

2. Function that can be passed into client should be in lower case and always be out of

{sum,sos,min,max}.

3. Once the UDP servers run, they run forever until stopped explicitly by typing ctr+C.

4. The TCP (AWS) server is active for one request only. After serving final answer to client for one particular 

function, TCP server closes and needs to be rerun.

5. On rerunning the TCP (AWS) server, although problem of ZOMBIE processes is handled, there is a time gap of

around 1 minute before the AWS server can be rerun.

-------------------------------------------------------

VI. Code Reusing

1. Some blocks of code are taken from Beej's guide for socket programming.
2. Additional help is taken from Sockets Tutorial on linuxhowtos.org

-------------------------------------------------------
