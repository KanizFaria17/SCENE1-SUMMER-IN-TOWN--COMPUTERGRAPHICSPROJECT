#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


//Declaring variables with initial values
float  tx = 10, rx = 10;

float sunAngle = 0.0f;  // Sun's current rotation angle
float cloudX = -160;  // Initial horizontal position of the clouds

float airplaneX = -200;

float roadLightStatus = 1; // 1 means ON, 0 means OFF
float roadLight2Status = 1; // 1 means ON, 0 means OFF

float backgroundColor[3] = {0.0, 0.9, 0.9};  // Default is day (sky blue)

float targetBackgroundColor[3] = {0.0, 0.9, 0.9};  // Target color for transitions
float transitionStep = 0.0;  // for smooth transitions
bool transitioning = false;
bool isDay = true;  // Initially it's day

void init(void);
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy);
void round(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy);

//Declaring draw functions
void bushes(void);  //O101
void flowers(void);  //O102
void greenary(void); //O103

void road (void); //O104
void roadBlock1(void); //O105
void roadBlock2(void); //O106
void roadBlock3(void); //O107
void roadBlock4(void); //O108
void roadBlock5(void); //O109
void roadBlock6(void); //O110
void roadBlock7(void); //O111

void building1(void); //O112
void building2(void); //O113
void building3(void); //O114
void building4(void); //O115
void building5(void); //O116
void building6(void); //O117
void building7(void); //O118
void building8(void); //O119

void sun(void); //O120
void tree(void); //O121
void tree2(void); //O122
void tree3(void); //O123
void cloud1(void); //O124
void cloud2(void); //O125
void aeroplane(void); //O126
void car(void); //O127
void truck(void); //O128
void roadLight(void); //O129
void roadLight2(void); //O130
void bench(void); //O131

void display(void);

//Declaring Mouse_Keyboard functions
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);  // Keyboard interaction function

//Transition functions
void updateSkyColor(int value); //A101
void transitionToDay(void); //A102
void transitionToNight(void); //A103
void updateSunPosition(int value); //A104
void updateCloudPosition(int value); //A105
void updateAeroplanePosition(int value); //A106
void updateCarPosition(int value); //A107
void updateTruckPosition(int value); //A108
int isPointInsideRoadLight(float x, float y, float lightX, float lightY, float radius); //A109


void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void round(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

//Implementing mouse-keyboard function
void mouse(int button, int state, int x, int y) {
    // Convert the mouse coordinates from window coordinates to OpenGL coordinates
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    y = windowHeight - y;  // Invert Y coordinate to match OpenGL's coordinate system

    // If the left mouse button is clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Toggle the road light states (no area check needed)
        roadLightStatus = 1 - roadLightStatus;
        roadLight2Status = 1 - roadLight2Status;
    }
    glutPostRedisplay();
}


void updateSkyColor(int value) //A101
{
    if (transitioning) {
        // Gradually change the sky color over time
        for (int i = 0; i < 3; i++) {
            backgroundColor[i] += (targetBackgroundColor[i] - backgroundColor[i]) * 0.05;  // Smooth step toward target color
        }

        // If the transition is complete, stop the transition
        if (fabs(targetBackgroundColor[0] - backgroundColor[0]) < 0.01 &&
            fabs(targetBackgroundColor[1] - backgroundColor[1]) < 0.01 &&
            fabs(targetBackgroundColor[2] - backgroundColor[2]) < 0.01) {
            transitioning = false;
        }
    }

    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 0);
    glutPostRedisplay();
    glutTimerFunc(50, updateSkyColor, 0);  // Keep updating the color
}

void transitionToDay() //A102
{
    // Set target color for day (light blue sky)
    targetBackgroundColor[0] = 0.0;
    targetBackgroundColor[1] = 0.9;
    targetBackgroundColor[2] = 0.9;
    transitioning = true;
    isDay = true;
}

void transitionToNight() //A103
{
    // Set target color for night (dark blue sky)
    targetBackgroundColor[0] = 0.0;
    targetBackgroundColor[1] = 0.0;
    targetBackgroundColor[2] = 0.2;
    transitioning = true;
    isDay = false;
}


void keyboard(unsigned char key, int x, int y) {
    if (key == 'd' || key == 'D') {
        if (!isDay) {
            // Transition from night to day
            transitionToDay();
        }
    }
    else if (key == 'n' || key == 'N') {
        if (isDay) {
            // Transition from day to night
            transitionToNight();
        }
    }
}

//Logic for object-drawing function
void bushes() //O101
{
    glColor3ub(0, 90, 0);
    glBegin(GL_POLYGON);
    glVertex2d(-70, -90); //i6
    glVertex2d(-60, -90); //j6

    glColor3ub(0, 90, 0);
    circle(5.5, 5.5, -70, -85); //S5
    circle(5, 5, -70, -80); //T5
    circle(5.5, 5.5, -60, -85); //V5
    circle(5, 5, -63, -81); //Z5
    circle(4, 4, -60, -77); //A6
}

void flowers() //O102
 {

    glColor3ub(255, 0, 203);
    circle(2, 2, -66, -75); //C6
    glColor3ub(255, 0, 100);
    circle(1.5, 1.5, -64, -75); //E6
    glColor3ub(255, 130, 45);
    circle(2, 2, -65, -72); //G6
    glColor3ub(126, 0, 128);
    circle(2.5, 2.5, -70, -74);
    glColor3ub(255, 0, 0);
    circle(2.5, 2.5, -61, -72);
}

void greenary() //O103
{
    //greenary above road
    glColor3ub(0, 159, 0);
    glBegin(GL_POLYGON);
    glVertex2d(-200, -100);
    glVertex2d(200, -100);
    glVertex2d(200, -50);
    glVertex2d(-200, -50);
    glEnd();
}

void road() //O104
{
    //car road(pitch)
    glColor3ub(50, 50, 50);
    glBegin(GL_POLYGON);
    glVertex2d(-200, -200);
    glVertex2d(200, -200);
    glVertex2d(200, -100);
    glVertex2d(-200, -100);
    glEnd();
}

 void roadBlock1() //O105
 {
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(-180, -160);
    glVertex2d(-140, -160);
    glVertex2d(-140, -140);
    glVertex2d(-180, -140);
    glEnd();
 }
void roadBlock2() //O106
{
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(-120, -160);
    glVertex2d(-80, -160);
    glVertex2d(-80, -140);
    glVertex2d(-120, -140);
    glEnd();
}

 void roadBlock3() //O107
 {
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(-60, -160);
    glVertex2d(-20, -160);
    glVertex2d(-20, -140);
    glVertex2d(-60, -140);
    glEnd();
 }

 void roadBlock4() //O108
 {
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, -160);
    glVertex2d(40, -160);
    glVertex2d(40, -140);
    glVertex2d(0, -140);
    glEnd();
 }

void roadBlock5() //O109
{
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(60, -160);
    glVertex2d(100, -160);
    glVertex2d(100, -140);
    glVertex2d(60, -140);
    glEnd();
}

void roadBlock6() //O110
{
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(120, -160);
    glVertex2d(160, -160);
    glVertex2d(160, -140);
    glVertex2d(120, -140);
    glEnd();
}

void roadBlock7() //O111
{
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(180, -160);
    glVertex2d(200, -160);
    glVertex2d(200, -140);
    glVertex2d(180, -140);
    glEnd();
}

void building1() //O112
{
    // Building 1 (FROM THE RIGHT)
    glColor3ub(216, 191, 216); // Dark Gray for the building
    glBegin(GL_POLYGON);
    glVertex2d(152,-50); //B1
    glVertex2d(152, 60);//C1
    glVertex2d(190, 70);//D1
    glVertex2d(200, 60);//H1
    glVertex2d(200, -50);//M1
    glEnd();
}

void building2() //O113
{
    glColor3ub(255, 182, 193);
    glBegin(GL_POLYGON);
    glVertex2d(130, -50); //U
    glVertex2d(124,-15); //V
    glVertex2d(124,24); //W
    glVertex2d(137.5, 45); //Z
    glVertex2d(152,38);  //A1
    glVertex2d(152, -50);  //B1
    glEnd();
}

void building3() //O114
{
    glColor3ub(230, 230, 120);
    glBegin(GL_POLYGON);
    glVertex2d(90, -50);  //Q
    glVertex2d(90, -30);  //R
    glVertex2d(100, -10); //S
    glVertex2d(130, -16);  //T
    glVertex2d(130, -50);  //S
    glEnd();
}

void building4() //O115
{
    glColor3ub(69, 169, 120);
    glBegin(GL_POLYGON);
    glVertex2d(85, -50);
    glVertex2d(44, -50);//T2
    glVertex2d(50, 50);//N
    glVertex2d(65, 70);//O
    glVertex2d(90, 50);//P
    glVertex2d(90, -50);//Q
    glEnd();
}

void building5() //O116
{
    glColor3ub(147, 112, 219);
    glBegin(GL_POLYGON);
    glVertex2d(44, -50); //T2
    glVertex2d(-60, -50); //V2
    glVertex2d(-60, 20);  //D3
    glVertex2d(49, 30);  //E3
    glVertex2d(46.6, 4);  //F3
    glEnd();
}

void building6() //O117
{
    glColor3ub(255, 182, 193);
    glBegin(GL_POLYGON);
    glVertex2d(-120, -50);//G3
    glVertex2d(-120, 40);//H3
    glVertex2d(-80, 60);//I3
    glVertex2d(-60, 40);//J3
    glVertex2d(-60, -50); //V2
    glEnd();
}

void building7() //O118
{
    glColor3ub(0, 0, 250);
    glBegin(GL_POLYGON);
    glVertex2d(-160, -50);//P3
    glVertex2d(-160, 20);//K3
    glVertex2d(-120, 0);//L3
    glVertex2d(-120, -50);//G3
    glEnd();
}

void building8() //O119
{
    glColor3ub(255, 120, 120);
    glBegin(GL_POLYGON);
    glVertex2d(-200, -50);//N1
    glVertex2d(-200, 100);//M3
    glVertex2d(-180, 120);//N3
    glVertex2d(-160, 100);//O3
    glVertex2d(-160, -50);//P3
    glEnd();

}


void sun() //O120
{
    float radius = 60.0f;  // Radius of the sun's orbit
    float centerX = 136.0954882378032;  // X-coordinate of the center
    float centerY = 142.3558675319782;  // Y-coordinate of the center

    // New sun position based on the angle
    float sunX = centerX + radius * cos(sunAngle);
    float sunY = centerY + radius * sin(sunAngle);

    glColor3ub(255, 255, 0);
    circle(22.642, 22.642, sunX, sunY);
}

void updateSunPosition(int value) //A104
{
    //sun's angle of rotation (in radians)
    sunAngle += 0.004f;  // for faster or slower rotation

    //range [0, 2*PI] to avoid overflow
    if (sunAngle > 2 * M_PI) {
        sunAngle -= 2 * M_PI;
    }

    glutPostRedisplay();
    glutTimerFunc(10, updateSunPosition, 0);
}

void tree1() //O121
{
    //tree1
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2d(25, -50);//W2
    glVertex2d(40, -50);//T2
    glVertex2d(40, -20);//S2
    glVertex2d(25,-14);//U2
    glEnd();

    glColor3ub(0, 128, 0);
    circle(8.8 , 8.8, 17, -19);//Z2
    circle(17, 17, 31, 0.5);//A3
    circle(12.6, 12.6, 7, -6);//B3
    circle(14.7, 14.7, 43, -7);//M
    glColor3ub(0, 100, 0);
    circle(12, 12, 58, 4);//V7
}

void tree2() //O122
{
    glColor3ub(75, 50, 25);
    glBegin(GL_POLYGON);
    glVertex2d(40, -50);//T2
    glVertex2d(50, -50);//M7
    glVertex2d(50, -20);//L7
    glVertex2d(40, -20);//S2

    //Bark
    glVertex2d(50, -30);//N7
    glVertex2d(60, -20);//O7
    glVertex2d(60, -22);//Q7
    glVertex2d(50, -35);//P7
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15, 15, 63, -18);//R7
    circle(13, 13, 77, -7);//T7
    circle(9, 9, 75, 6);//Z7
}

void tree3() //O123
{
    glColor3ub(0, 100, 0); //UP(E7)
    circle(15.5, 15.5, -111, -30);
    glColor3ub(0, 100, 0);
    circle(6, 6, -121, -51);//W6
    circle(6, 6, -125, -47);//A7
    circle(10, 10, -131, -37);//C7
    circle(10.6, 10.6, -90, -38);//G7
    circle(5, 5, -102, -45);//I7
    circle(5, 5, -94, -47);//J7

    glColor3ub(75, 50, 25);
    glBegin(GL_POLYGON);
    glVertex2d(-110, -74);  //06
    glVertex2d(-115, -75);  //K6
    glVertex2d(-115, -40); //L6
    glVertex2d(-105, -40);  //N6
    glVertex2d(-105, -60); //M6

    //Bark1
    glVertex2d(-105, -50);//p6
    glVertex2d(-97, -41);//q6
    glVertex2d(-97, -43);//s6
    glVertex2d(-105, -55);//r6

    //Bark2
    glVertex2d(-115, -48);//u6
    glVertex2d(-123, -41);//v6
    glVertex2d(-123, -39);//t6
    glVertex2d(-115, -45);//l6
    glEnd();
}

// Timer function to update the cloud's position
void updateCloudPosition(int value) //A105
{
    cloudX += 0.3;  // Move clouds to the right by 0.3 units per update

    if (cloudX > 200)  // Reset the clouds' position once they go off-screen
        cloudX = -200;

    glutPostRedisplay();
    glutTimerFunc(20, updateCloudPosition, 0);
}

void cloud1() //O124
{
    glColor3ub(255, 255, 255);
    circle(14.9, 14.9, cloudX, 160);  // Cloud 1
    circle(14, 14, cloudX + 14, 164);  // Cloud 2
    circle(13.8, 13.8, cloudX + 28, 167);  // Cloud 3
}

void cloud2() //O125
{
    glColor3ub(255, 255, 255);
    circle(13, 13, cloudX + 72, 140);  // Cloud 4
    circle(13, 13, cloudX + 84, 137);  // Cloud 5
    circle(12, 12, cloudX + 96, 143);  // Cloud 6
}

void updateAeroplanePosition(int value) //A106
{
    airplaneX += 2;  // Move the airplane by 2 units per update

    if (airplaneX > 200)  // Reset the airplane position once it goes off-screen
        airplaneX = -200;

    glutPostRedisplay();
    glutTimerFunc(20, updateAeroplanePosition, 0);
}

void aeroplane() //O126
{
    glColor3ub(170, 170, 170);
    glBegin(GL_POLYGON);
    // Body
    glVertex2d(-10 + airplaneX, 180); // B8
    glVertex2d(40 + airplaneX, 180);  // C8
    glVertex2d(49.7 + airplaneX, 174);  // D8
    glVertex2d(40 + airplaneX, 170); // E8
    glVertex2d(-10 + airplaneX, 170); // F8
    glVertex2d(-14 + airplaneX, 168); // M8
    glVertex2d(-20 + airplaneX, 165); // N8
    glVertex2d(-16 + airplaneX, 172); // O8
    glVertex2d(-20 + airplaneX, 184); // P8
    glVertex2d(-16 + airplaneX, 184); // Q8
    glEnd();

    // WingU
    glColor3ub(250, 250, 250);
    glBegin(GL_POLYGON);
    glVertex2d(31.6 + airplaneX, 180); // J8
    glVertex2d(10 + airplaneX, 190); // K8
    glVertex2d(22 + airplaneX, 180); // L8
    glEnd();

    // WingL
    glColor3ub(200, 200, 200);
    glBegin(GL_POLYGON);
    glVertex2d(30 + airplaneX, 170); // G8
    glVertex2d(10 + airplaneX, 163); // H8
    glVertex2d(18 + airplaneX, 170.7); // I8
    glEnd();
}

void car() //O127
{
    // Car body
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(32 + tx, -100); // Move car along X axis with tx
    glVertex2d(132 + tx, -100);
    glVertex2d(138 + tx, -122);
    glVertex2d(32 + tx, -122);
    glEnd();

    // Car roof
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(40 + tx, -100);
    glVertex2d(60 + tx, -80);
    glVertex2d(100 + tx, -80);
    glVertex2d(120 + tx, -100);
    glEnd();

    // Back windows
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(48+ tx, -100);
    glVertex2d(61+ tx, -87);
    glVertex2d(75+ tx, -87);
    glVertex2d(75+ tx, -100);
    glEnd();

    // Front window
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(112 + tx, -100);
    glVertex2d(100+ tx, -87);
    glVertex2d(80+ tx, -87);
    glVertex2d(80 + tx, -100);
    glEnd();

    // Car wheels
    glColor3ub(0, 0, 0);
    round(10, 10, 110 + tx, -120);  // Wheels will also move with tx
    round(10, 10, 60 + tx, -120);
}

// Timer function to move the car
void updateCarPosition(int value) //A107
{
    tx += 3;  // Move the car by 2 units per update

    if (tx > 200)  // Reset the car position to left once it goes off-screen
        tx = -200;

    glutPostRedisplay();
    glutTimerFunc(40, updateCarPosition, 0);
}

void truck() //O128
{
    // Truck body
    glColor3ub(204, 0, 204);
    glBegin(GL_POLYGON);
    glVertex2d(-120 +tx, -80); //Z8
    glVertex2d(-80 +tx, -80); //N5
    glVertex2d(-60 +tx, -100); //A9
    glVertex2d(-60 +tx, -120); //S8
    glVertex2d(-120 +tx, -120); //W8
    glEnd();

    //Window
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(-120 +tx, -87);//B9
    glVertex2d(-80 +tx, -87);//C9
    glVertex2d(-67 +tx, -100);//D9
    glVertex2d(-120 +tx, -100);//E9
    glEnd();

    // Truck cabin
    glColor3ub(152, 255, 152);
    glBegin(GL_POLYGON);
    glVertex2d(-105 +tx, -120);//W8
    glVertex2d(-180 +tx, -120);//T8
    glVertex2d(-180 +tx, -70);//U8
    glVertex2d(-105 +tx, -70);//V8
    glEnd();

    //Truck wheels
    glColor3ub(0, 0, 0);
    round(13, 13, -167 +tx, -120); //F9
    round(13, 13, -107 +tx, -120);
}

// Timer function to move the truck
void updateTruckPosition(int value) //A108
{
    tx += 2;  // Move the truck by 2 units per update

    if (tx > 200)  // Reset the truck position to left once it goes off-screen
        tx = -200;

    glutPostRedisplay();
    glutTimerFunc(40, updateCarPosition, 0);
}

int isPointInsideRoadLight(float x, float y, float lightX, float lightY, float radius) //A109
{
    float distance = sqrt((x - lightX) * (x - lightX) + (y - lightY) * (y - lightY));
    return (distance <= radius);
}

void roadLight() //O129
{
    // Road light pole
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(-170, -100); //E1
    glVertex2d(-170, -40);  //S4
    glVertex2d(-165, -40);  //T4
    glVertex2d(-165, -100);  //Q4
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(-180, -50);  //E4
    glVertex2d(-155, -50);  //F4
    glVertex2d(-155, -55);  //O4
    glVertex2d(-180, -55);  //F1
    glEnd();

    // Road light head
    if (roadLightStatus)
        glColor3ub(255, 255, 100); // Light ON (Yellow)
    else
        glColor3ub(255, 255, 255); // Light OFF (Gray)

    circle(6.5, 6.5, -167.5, -33);

}

void roadLight2() //O130
{
    // Road light pole 2
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(165, -100); //U4
    glVertex2d(165, -40);  //R4
    glVertex2d(170, -40);  //P4
    glVertex2d(170, -100);  //G1
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(155, -50);  //Z4
    glVertex2d(180, -50);  //A5
    glVertex2d(180, -55);  //B5
    glVertex2d(155, -55);  //C5
    glEnd();

    // Road light head
     if (roadLight2Status)
        glColor3ub(255, 255, 100); // Light ON (Yellow)
    else
        glColor3ub(255, 255, 255); // Light OFF (White)

    circle(7, 7, 167, -33);
}

void bench() //O131
{
    // bench
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2d(-110, -70); //F5
    glVertex2d(-80, -70);  //G5
    glVertex2d(-75, -75);  //H5
    glVertex2d(-105, -75);  //J5
    glEnd();

    //benchLeg1
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2d(-110, -80);  //K5
    glVertex2d(-110, -70);  //F5
    glVertex2d(-105, -75);  //J5
    glVertex2d(-105, -85);  //L5
    glEnd();

    //benchLeg2
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2d(-80, -80);  //N5
    glVertex2d(-80, -70);  //G5
    glVertex2d(-75, -75);  //H5
    glVertex2d(-75, -85);  //M5
    glEnd();

    //benchBack
    glColor3ub(181, 131, 90);
    glBegin(GL_POLYGON);
    glVertex2d(-110, -70);  //F5
    glVertex2d(-110, -60);  //O5
    glVertex2d(-80, -60);  //P5
    glVertex2d(-80, -70);  //G5
    glEnd();

    //benchSideL
    glColor3ub(181, 131, 90);
    glBegin(GL_POLYGON);
    glVertex2d(-110, -70);  //F5
    glVertex2d(-110, -60);  //O5
    glVertex2d(-108.5, -67.5);  //R5
    glVertex2d(-105, -75);  //J5
    glEnd();

    //benchSideR
    glColor3ub(181, 131, 90);
    glBegin(GL_POLYGON);
    glVertex2d(-80, -70);  //G5
    glVertex2d(-80, -60);  //P5
    glVertex2d(-78, -68);  //Q5
    glVertex2d(-75, -75);  //H5
    glEnd();

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    greenary(); //O103
    road(); //O104
    roadBlock1(); //O105
    roadBlock2(); //O106
    roadBlock3(); //O107
    roadBlock4(); //O108
    roadBlock5(); //O109
    roadBlock6(); //O110
    roadBlock7(); //O111
    sun(); //O120
    building1(); //O112
    building2(); //O113
    building3(); //O114
    building4(); //O115
    building5(); //O116
    building6(); //O117
    building7(); //O118
    building8(); //O119
    tree1(); //O121
    tree2(); //O122
    tree3(); //O123
    bushes(); //O101
    flowers(); //O102
    cloud1(); //O124
    cloud2(); //O125
    aeroplane(); //O126
    roadLight(); //O129
    roadLight2(); //O130
    bench(); //O131
    car(); //O127
    truck(); //O128
    glFlush();
}

void init(void) {
    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);

    glutTimerFunc(10, updateSunPosition, 0);
    glutTimerFunc(50, updateSkyColor, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Summer In Town");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(40, updateCarPosition, 0); //A107
    glutTimerFunc(40, updateTruckPosition, 0); //A108
    glutTimerFunc(20, updateCloudPosition, 0); //A105
    glutTimerFunc(20, updateAeroplanePosition, 0); //A106
    glutMainLoop();
    return 0;
}
