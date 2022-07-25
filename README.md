# pycnc
Control your grbl-compatible cnc using python. 

## Setup
- Flash cnc_control to Arduino
- Drag python/cnc.py to directory of python project

## Usage
```python
import cnc
Cnc = cnc.cnc("serial port of cnc")

*

Cnc.done()
```

### Supported commands
```python
pen_up() #duh
pen_down() #duh
move_to(x, y) #moves pen to coord
draw_line(starting_x, starting_y, ending_x, ending_y) #moves pen to coord then draws a line until ending coord
draw_image(path_to_img, width, height) #draws an image provided the path
move_x() #moves pen along x axis; faster than move_to() for single axis movement
move_y() #moves pen along y axis; faster than move_to() for single axis movement
done() #must call at the end of code
```

## Requirements
- Arduino IDE
- Pyserial
- Numpy
- PIL
