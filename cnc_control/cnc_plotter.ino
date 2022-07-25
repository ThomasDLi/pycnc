#include <Servo.h>

//x axis pins
#define xax 2 //cnc x axis pulse pins
#define xdir 5 //cnc x axis direction pins

//y axis pins
#define yax 3 //cnc y axis pulse pins
#define ydir 6 //cnc y axis direction pins

//z axis servo
Servo penHolder;
#define zpin 11

//z axis servo values
const int pen_up_val = 90;
const int pen_down_val = 180;

//relative coordinate position to origin
int posit_x = 0;
int posit_y = 0;

//set default stepping speed
int stepping_speed = 1500;

//temporary variables to stop memory leak
float dif_dist;
int resolution;
int dif_coord;
int dist_per_point;
String data;

void setup() {

  Serial.begin(9600);

  pinMode(xax, OUTPUT);
  pinMode(yax, OUTPUT);
  pinMode(xdir, OUTPUT);
  pinMode(ydir, OUTPUT);

  //z axis definition
  penHolder.attach(zpin);

  //put pen in ready position
  pen_up();

}

void loop() {

  //inform python code it is ready
  Serial.println("ready");

  if (Serial.available() > 0) {

    data = String(Serial.readStringUntil("\n"));

    Serial.println(data.substring(0, 1));
    Serial.println(data.substring(1));

    //(number corrisponding to instruction) (number of steps / IF OPERATION 5, CM FROM LEFT TO RIGHT)

    switch (data.substring(0, 1).toInt()) {

      case 4:
        pen_up();
        break;

      case 5:
        pen_down();
        break;

      case 6:
        draw_line(posit_x, posit_y, data.substring(1, 4).toInt(), data.substring(4, 7).toInt(), data.substring(7, 10).toInt(), data.substring(10, 13).toInt());
        break;

      case 7:
        move_to(posit_x, posit_y, data.substring(1, 4).toInt(), data.substring(4, 7).toInt());
        break;

      case 8:
        draw_image(data.substring(1, 4).toInt(), data.substring(4, 7).toInt(), data.substring(7));
        break;

      case 0:
        move_x(posit_x, data.substring(1).toInt());
        break;

      case 1:
        move_y(posit_y, data.substring(1).toInt());
        break;

    }

  }

  delay(500);

}
