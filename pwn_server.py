#-*- coding: utf-8 -*-

import socket
import os
import sys
import subprocess

HOST = '127.0.0.1'
PORT = 28080

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind((HOST, PORT))

sock.listen(5)

while True:
    con, addr = sock.accept()
    pid = os.fork()

    if pid == 0:
        print("run server")
        cmd = "python hello_world.py"
#    cmd = "pwd"
        subprocess.call(cmd.split())
        sys.exit()
