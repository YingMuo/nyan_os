#!/usr/bin/env python3
from pwn import *
from time import sleep

kernel = open('./kernel8.img', 'rb').read()
# r = serialtube('/dev/tty.serial-0000', convert_newlines=False)
r = serialtube('/dev/pts/4', convert_newlines=False)
sleep(5)
# print(r.read())
r.write(p32(len(kernel)))
print(r.read())
sleep(1)
r.write(kernel)
print(r.read())
r.close()
