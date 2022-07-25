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
pen_up()
pen_down()
move_to(x, y)
draw_line(starting_x, starting_y, ending_x, ending_y)
Cnc.draw_image(path_to_img, width, height)
done()
```

## Requirements
- Arduino IDE
- Pyserial
- Numpy
- PIL
