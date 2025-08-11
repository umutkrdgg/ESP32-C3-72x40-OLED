#include <Wire.h>
#include <U8g2lib.h>
#include <math.h>

  //SCL -->GPIO6
  //SDA -->GPIO5
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

float cubeVerts[8][3] = {
  {-1, -1, -1},
  { 1, -1, -1},
  { 1,  1, -1},
  {-1,  1, -1},
  {-1, -1,  1},
  { 1, -1,  1},
  { 1,  1,  1},
  {-1,  1,  1}
};

int edges[12][2] = {
  {0,1},{1,2},{2,3},{3,0},
  {4,5},{5,6},{6,7},{7,4},
  {0,4},{1,5},{2,6},{3,7}
};

float angleX = 0;
float angleY = 0;

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();

  float cx = 36;  // center X
  float cy = 20;  // center Y

  float projected[8][2];

  for (int i = 0; i < 8; i++) {
    float x = cubeVerts[i][0];
    float y = cubeVerts[i][1];
    float z = cubeVerts[i][2];

    float y1 = y * cos(angleX) - z * sin(angleX);
    float z1 = y * sin(angleX) + z * cos(angleX);

    float x2 = x * cos(angleY) + z1 * sin(angleY);
    float z2 = -x * sin(angleY) + z1 * cos(angleY);

    // change scale
    float scale = 30 / (z2 + 4); 
    projected[i][0] = x2 * scale + cx;
    projected[i][1] = y1 * scale + cy;
  }

  for (int i = 0; i < 12; i++) {
    int p1 = edges[i][0];
    int p2 = edges[i][1];
    u8g2.drawLine(
      projected[p1][0], projected[p1][1],
      projected[p2][0], projected[p2][1]
    );
  }

  u8g2.sendBuffer();

  angleX += 0.05;
  angleY += 0.07;

  //speed
  delay(30);
}
