/*

ECE 209 Section 051

This program implements a simple tracking
device, capable of receiving 2-dimensional
coordinates, linear road approximations
and time delays to calculate distance travelled,
velocity, changing roads and changes in direction.

The user interfaces with the program by entering
the time elapsed since the last coordinate was
sent, followed by x and y double coordinates.

Once halted, the user may enter either an EOF
or non-numeric character to exit execution and
receive data about their trip.

Author: Sam Messick
Last Modified: June 25, 2017

*/


#include <stdio.h>
#include <math.h>

#ifndef SECRET_TESTS
double M1 = -1.0, B1 = 0; // Road 1 slope and intercept
double M2 = 1.0, B2 = 0;  // Road 2 slope and intercept
#else
double M1 = SECRET_M1, B1 = SECRET_B1; // Secret Road 1 slope and intercept
double M2 = SECRET_M2, B2 = SECRET_B2; // Secret Road 2 slope and intercept
#endif

int Road = 1, First_road = 1;          // Road initialization
int Changed_direction = 0;             // Number of times changed direction
int Changed_road = 0;                  // Number of times changed road
double Total_distance = 0.0;           // Total distance travelled
double Peak_speed = 0.0;               // Maximum speed while travelling

void track(double x, double y, double time);  // Tracks movement
double get_y(double x, int road);             // Outputs y value given x value and road
double x_intercept(void);                     // Outputs x-value of lines' intercept
double distance(double x1, double y1, double x2, double y2); // Provides distance between current point and previous
double nearest_point_on_road(double x, double y, int road);  // Provides the nearest x value on given road to given coordinates
int closest_road(double x, double y, int road);              // Provides the closest road to given coordinates


int  main() {
  double time, x, y;  // Cartesian coordinates and total time
  int ret;            // Return value from scanf()
  do {
    /* get time, x, y coordinates from stdin */
    ret = scanf("%lf%lf%lf", &time, &x, &y);
    if(ret == 3 /* Valid coordinates and time scanned*/)
      {
        /* call tracking algorithm */
        track(x, y, time);
      }
  } while(ret == 3 /* Valid coordinates and time scanned */);
  Road = closest_road(x, y, Road);

  /* Print out final measurements */
  printf("Total distance = %.2lf\n", Total_distance);
  printf("Peak speed = %.2lf\n", Peak_speed);
  printf("# of changes in direction = %d\n", Changed_direction);
  printf("# of changes in road = %d\n", Changed_road);
  printf("First Road = %d, Last Road = %d\n", First_road, Road);

  return 0;
}

/* Tracks the distance travelled by a point between function   *
 * calls. Based on the call, the tracking function takes       *
 * different actions. Over various calls, the function updates *
 * current_speed, Peak_speed, Total_distance, Changed_road,    */
void track(double x, double y, double time) {
  static double distance_travelled;   // Distance travelled during function call
  static double current_speed;        // Speed measured during function call
  static int track_call_count = 1;    // Number of times track is called
  static double delta_x;              // Current change in x coordinate
  static double delta_y;              // Current change in y coordinate
  typedef struct {
    double x;        // Previous x value
    double y;        // Previous y value
    double delta_x;  // Previous change in x coordinate
    double delta_y;  // Previous change in y coordinate
    double Road;     // Previous Road
  } prior;
  static prior previous;  // Struct for simplifying variable grouping
  int no_turn = 1;        // Truth value for whether or not the point changed roads

  // First tracking measurement
  if(track_call_count == 1 /* first function call */) {
    First_road = closest_road(x, y, Road);
    previous.Road = First_road;  // Store road for next call
    previous.x = nearest_point_on_road(x, y, previous.Road);  // Store projected x
    previous.y = get_y(previous.x, previous.Road);            // Store projected y
  } else /* Additional tracking measurement */ {
    Road = closest_road(x, y, Road);  // Find closest road
    x = nearest_point_on_road(x, y, Road);  // Projected x
    y = get_y(x, Road);                     // Projected y
    if(previous.Road != Road /* changed road */) {
      Changed_road++;
      Changed_direction++;
      /* Add distance from previous point to intersection *
       * with distance from intersection to current point */
      distance_travelled = distance(previous.x, previous.y, x_intercept(), get_y(x_intercept(), Road))
                          + distance(x, y, x_intercept(), get_y(x_intercept(), Road));
      delta_x = x - x_intercept();                // Update movement measurements
      delta_y = y - get_y(x_intercept(), Road);
      no_turn--;
    } else {
      distance_travelled = distance(previous.x, previous.y, x, y); // Update movement measurements
      delta_x = x - previous.x;
      delta_y = y - previous.y;
    }
    if((track_call_count > 2) && no_turn && ( /* delta_x or y changed sign between calls */
       (-delta_x > 0 && previous.delta_x > 0) || (-delta_x < 0 && previous.delta_x < 0) ||
       (-delta_y > 0 && previous.delta_y > 0) || (-delta_y < 0 && previous.delta_y < 0)))
           Changed_direction++;
    /* Update total measurements */
    Total_distance += distance_travelled;
    current_speed = distance_travelled / time;
    if(current_speed > Peak_speed)
      Peak_speed = current_speed;
    /* Store data for next call */
    previous.x = x;
    previous.y = y;
    previous.delta_x = delta_x;
    previous.delta_y = delta_y;
    previous.Road = Road;
  }
  track_call_count++;
}

/* Return y value for given x value and road number using *
 * Given slope and y-intercept of road.                   */
double get_y(double x, int road) {
  if(road == 1) return M1*x+B1;
  else return M2*x+B2;
}

/* Return x-intercept of given roads. */
double x_intercept(void) {
  return (B2 - B1)/(M1-M2);
}

/* Return distance between two points */
double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

/* Return x value for nearest point from given coordinates   *
 * to given road. Calculates normal slope of road and        *
 * determines x intercept of normal line through coordinates *
 * and appropriate road.                                     */
double nearest_point_on_road(double x, double y, int road) {
  static int normal;  // Normal slope of road
  if(road == 1) normal = -1/M1;
  else normal = -1/M2;
  if(road == 1)
    return (y - normal*x - B1)/(M1 - normal);
  else return (y - normal*x - B2)/(M2 - normal);
}

/* Return closest road to coordinates. Input road serves to         *
 * shorten execution time. Compares the distance to each road with  *
 * nearest_point_on_road() and distance().                          */
int closest_road(double x, double y, int road) {
  double r1 = nearest_point_on_road(x, y, road);      // Nearest point on road
  double d1 = distance(x, y, r1, get_y(r1, road));     // Distance to road
  double r2 = nearest_point_on_road(x, y, 3 - road);   // Nearest point on other road
  double d2 = distance(x, y, r2, get_y(r2, 3 - road)); // Distance to other road

  /* The coordinates are incredibly close to road */
  if(d1 < .0001)
    return road;
  /* The tracking point is equidistant from each road */
  else if(d1 == d2)
    return road;
  /* The tracking point is closer to the parameter road */
  else if(d1 < d2)
    return road;
  /* The tracking point is closer to the other road */
  else
    return 3 - road;
}
                  /*;,_            ,
                 _uP~"b          d"u,
                dP'   "b       ,d"  "o
               d"    , `b     d"'    "b
              l] [    " `l,  d"       lb
              Ol ?     "  "b`"=uoqo,_  "l
            ,dBb "b        "b,    `"~~TObup,_
          ,d" (db.`"         ""     "tbc,_ `~"Yuu,_
        .d" l`T'  '=                      ~     `""Yu,
      ,dO` gP,                           `u,   b,_  "b7
     d?' ,d" l,                           `"b,_ `~b  "1
   ,8i' dl   `l                 ,ggQOV",dbgq,._"  `l  lb
  .df' (O,    "             ,ggQY"~  , @@@@@d"bd~  `b "1
 .df'   `"           -=@QgpOY""     (b  @@@@P db    `Lp"b,
.d(                  _               "ko "=d_,Q`  ,_  "  "b,
Ql         .         `"qo,._          "tQo,_`""bo ;tb,    `"b,
qQ         |L           ~"QQQgggc,_.,dObc,opooO  `"~~";.   __,7,
qp         t\io,_           `~"TOOggQV""""        _,dg,_ =PIQHib.
`qp        `Q["tQQQo,_                          ,pl{QOP"'   7AFR`
  `         `tb  '""tQQQg,_             p" "b   `       .;-.`Vl'
             "Yb      `"tQOOo,__    _,edb    ` .__   /`/'|  |b;=;.__
                           `"tQQQOOOOP""`"\QV;qQObob"`-._`\_~~-._
                                """"    ._        /   | |oP"\_   ~\ ~\_~\
                                        `~"\ic,qggddOOP"|  |  ~\   `\~-._
                                          ,qP`"""|"   | `\ `;   `\   `\
                               _        _,p"     |    |   `\`;    |    |
                               "boo,._dP"       `\_  `\    `\|   `\   ;
                                 `"7tY~'            `\  `\    `|_   |
                                                      `~\  *| */
