#-*- coding: utf-8 -*-

import socket

HOST = '127.0.0.1'
PORT = 8080

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind((HOST, PORT))

sock.listen(5)

while True:
    con, addr = sock.accept()
