import cnc

Cnc = cnc.cnc("/dev/cu.usbmodem1101")

Cnc.draw_line(0, 0, 20, 20)

Cnc.done()
