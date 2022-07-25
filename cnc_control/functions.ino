//function_family: pen movement
//description: moves pen
//arguments: none
//return value: none
void pen_down() {

  penHolder.write(pen_down_val);

}

//function_family: pen movement
//description: moves pen
//arguments: none
//return value: none
void pen_up() {

  penHolder.write(pen_up_val);

}

//function_family: utility functions
//description: gets the amount of intermited points between two 1D coordinates
//arguments: Line's starting and ending values, resolution, and for loop's iteration count.
//return value: point between two coordinates at current for loop iteration
int points(int start_val, int fin_val, int res, int iter) {

  dif_coord = fin_val - start_val;

  dist_per_point = dif_coord / res;

  return dist_per_point * iter + start_val;

}

//function_family: draw image
//description: draws image imported over python
//arguments: image width, image height, image (converted to bits)
//return value: none
void draw_image(int width, int height, String image) {

  for (int x = 0; x < width; x++) {

    for (int y = 0; y < height; y++) {  

      move_x(posit_x, x * 5);
      move_y(posit_y, y * 5);

      Serial.println(image[(x * height) + y]);

      if(image[(x * height) + y] == '0'){

          pen_down();
          delay(50);
          pen_up();
          delay(50);
        
        }

    }

  }

}

//function_family: move to 2d coordinate
//description: moves to 2d coordinate
//arguments: current x position, current y position, distination x position, destination y position
//return value: none
void move_to(float cur_x, float cur_y, float end_x, float end_y) {
  resolution = min(abs(end_x - cur_x), abs(end_y - cur_y));

  for (int x = 0; x < (resolution + 2); x++) {

    move_x(posit_x, points(cur_x, end_x, resolution, x));
    move_y(posit_y, points(cur_y, end_y, resolution, x));

  }

}

//function_family: draw line
//description: draws a line
//arguments: current position of pen's x axis, current position of pen's y axis, and starting/ending coordinates for the line
//return value: none
void draw_line(float cur_x, float cur_y, float start_x, float start_y, float end_x, float end_y) {

  if (cur_x != start_x && cur_y != start_y) {

    pen_up();
    move_to(cur_x, cur_y, start_x, start_y);
    pen_down();

  }

  move_to(start_x, start_y, end_x, end_y);

}

//function_family: draw shape
//description: draws a rectangle
//arguments: coordinates of pen, and coordinats for two opposite corners of the rectangle.
//return value: none
void draw_rectangle(float cur_x, float cur_y, float start_x, float start_y, float end_x, float end_y) {

  if (cur_x != start_x && cur_y != start_y) {

    pen_up();
    move_to(cur_x, cur_y, start_x, start_y);
    pen_down();

  }

  move_to(start_x, start_y, end_x, start_y);
  move_to(end_x, start_y, end_x, end_y);
  move_to(end_x, end_y, start_x, end_y);
  move_to(start_x, end_y, start_x, start_y);
  move_to(start_x, start_y, end_x, start_y);

}

//function_family: draw single axis line
//description: draws a line from given values x axis
//arguments: current position of pen's x axis, the line's starting point, the line's ending point
//return value: none
void draw_line_x(float cur_x, float start_x, float end_x) {

  if (cur_x != start_x) {

    pen_up();
    move_x(cur_x, start_x);
    pen_down();

  }

  move_x(start_x, end_x);

}

//function_family: draw single axis line
//description: draws a line from given values y axis
//arguments: current position of pen's y axis, the line's starting point, the line's ending point
//return value: none
void draw_line_y(float cur_y, float start_y, float end_y) {

  if (cur_y != start_y) {

    pen_up();
    move_y(cur_y, start_y);
    pen_down();

  }

  move_y(start_y, end_y);

}

//function_family: single axis absolute coordinate movement
//description: moves pen to an absolute x axis coordinate
//arguments: current position of pen's y axis, the new y axis position to move to
//return value: none
void move_x(float current_pos, float new_pos) {

  //get the distance needed to move
  dif_dist = new_pos - current_pos;

  //logic to make value absolute and to set direction pins
  if (dif_dist > 0) {

    digitalWrite(xdir, LOW);

  }

  else if (dif_dist < 0) {

    digitalWrite(xdir, HIGH);
    dif_dist = dif_dist * -1;

  }

  else if (dif_dist == 0) {

    return;

  }

  //move
  for (int x = 0; x < (dif_dist * 5); x++) {

    digitalWrite(xax, HIGH);
    delayMicroseconds(1500);
    digitalWrite(xax, LOW);
    delayMicroseconds(1500);

  }

  posit_x = new_pos;

}

//function_family: single axis absolute coordinate movement
//description: moves pen to an absolute y axis coordinate
//arguments: current position of pen's y axis, the new y axis position to move to
//return value: none
void move_y(float current_pos, float new_pos) {

  //get the distance needed to move
  dif_dist = new_pos - current_pos;

  //logic to make value absolute and to set direction pins
  if (dif_dist > 0) {

    digitalWrite(ydir, LOW);

  }

  else if (dif_dist < 0) {

    digitalWrite(ydir, HIGH);
    dif_dist = dif_dist * -1;

  }

  else if (dif_dist == 0) {

    return;

  }

  //move

  for (int x = 0; x < (dif_dist * 5); x++) {

    digitalWrite(yax, HIGH);
    delayMicroseconds(1500);
    digitalWrite(yax, LOW);
    delayMicroseconds(1500);

  }

  posit_y = new_pos;

}

//function_family: basic movement
//description: moves pen left (steps)
//arguments: steps to move
//return value: none
void left(int steps) {

  digitalWrite(xdir, LOW);

  for (int x = 0; x < steps; x++) {

    digitalWrite(xax, HIGH);
    delayMicroseconds(stepping_speed);
    digitalWrite(xax, LOW);
    delayMicroseconds(stepping_speed);

  }

}

//function_family: basic movement
//description: moves pen right (steps)
//arguments: steps to move
//return value: none
void right(int steps) {

  digitalWrite(xdir, HIGH);

  for (int x = 0; x < steps; x++) {

    digitalWrite(xax, HIGH);
    delayMicroseconds(stepping_speed);
    digitalWrite(xax, LOW);
    delayMicroseconds(stepping_speed);

  }

}

//function_family: basic movement
//description: moves pen up (steps)
//arguments: steps to move
//return value: none
void up(int steps) {

  digitalWrite(ydir, LOW);

  for (int x = 0; x < steps; x++) {

    digitalWrite(yax, HIGH);
    delayMicroseconds(stepping_speed);
    digitalWrite(yax, LOW);
    delayMicroseconds(stepping_speed);

  }

}

//function_family: basic movement
//description: moves pen down (steps)
//arguments: steps to move
//return value: none
void down(int steps) {

  digitalWrite(ydir, HIGH);

  for (int x = 0; x < steps; x++) {

    digitalWrite(yax, HIGH);
    delayMicroseconds(stepping_speed);
    digitalWrite(yax, LOW);
    delayMicroseconds(stepping_speed);

  }

}
