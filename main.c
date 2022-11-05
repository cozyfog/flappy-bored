#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "base.h"
#include <stdio.h>
#include <string.h>
#include "stb_image.h"

local f32 bird_pos = 2.0f, bird_vel = 0.0f;
local V2 pipe0_pos = {9.0f, 0.0f};
local i64 score = 0;
local b8 score_claimed = false;
local unsigned int bird_texture_id, pipe0_texture_id;

fn loadTexture(string location, i8 id)
{
  unsigned int texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  i32 width, height, channels;
  unsigned char *data = stbi_load(location, &width, &height, &channels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  switch (id)
  {
    case 0:
      bird_texture_id = texture_id;
    case 1:
      pipe0_texture_id = texture_id;
  }
}

fn restart()
{
  bird_vel = 0.0f;
  bird_pos = 2.0f;
  pipe0_pos = (V2){9.0f, 0.0f};
  score = 0;
  score_claimed = false;
}

fn init()
{
  glOrtho(0.0f, 9.0f, 13.0f, 0.0f, -1.0f, 1.0f);
  glClearColor(0.5f, 0.7f, 0.8f, 1.0f);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  loadTexture("bird.png", 0);
  loadTexture("box.png", 1);
}

fn drawQuad(V2 pos, f32 height)
{
  glPushMatrix();
  glColor4d(1.0f, 1.0f, 1.0f, 1.0f);
  glTranslated(pos.x, pos.y, 0);
  glScalef(1.0f, height, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2i(0, 0); glVertex2f(0.0f, 0.0f);
  glTexCoord2i(1, 0); glVertex2f(1.0f, 0.0f);
  glTexCoord2i(1, 1); glVertex2f(1.0f, 1.0f);
  glTexCoord2i(0, 1); glVertex2f(0.0f, 1.0f);
  glEnd();
  glPopMatrix();
}

fn display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  srand(glutGet(GLUT_ELAPSED_TIME));

  bird_vel += 0.007f;
  bird_pos += bird_vel;

  pipe0_pos.x -= 0.05f;
  if (pipe0_pos.x <= -1.0f)
  {
    pipe0_pos.x = 10.0f;
    pipe0_pos.y = rand() % 6 - 2;
  }

  if ((int)(pipe0_pos.x) == 2 || (int)(pipe0_pos.x) == 3)
  {
    if (bird_pos > pipe0_pos.y + 8.0f || bird_pos < pipe0_pos.y + 5.0f)
    {
      restart();
    }
    else if (!score_claimed)
    {
      score++;
      score_claimed = true;
    }
  }
  else
  {
    score_claimed = false;
  }

  glBindTexture(GL_TEXTURE_2D, bird_texture_id);
  drawQuad((V2){3.0f, bird_pos}, 1.0f); // Drawing the bird

  glBindTexture(GL_TEXTURE_2D, pipe0_texture_id);
  drawQuad((V2){pipe0_pos.x, pipe0_pos.y - 5.0f}, 10.0f);
  drawQuad((V2){pipe0_pos.x, pipe0_pos.y + 9.0f}, 10.0f);

  glDisable(GL_TEXTURE_2D);
  glRasterPos2f(4.0f, 0.5f);
  char counter_string[512];
  sprintf(counter_string, "%d", score);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)(counter_string));
  glEnable(GL_TEXTURE_2D);

  glutSwapBuffers();
  glutPostRedisplay();
}

fn keyboard(unsigned char key, i32 x, i32 y)
{
  bird_vel = -0.15f;
}

b8 main(i32 argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(400, 600);
  glutInitWindowPosition((i32)((glutGet(GLUT_SCREEN_WIDTH) - 400) * 0.5f), (i32)((glutGet(GLUT_SCREEN_HEIGHT) - 600) * 0.5f));
  glutCreateWindow("i3float"/*"Flappy Bored (Development Build)"*/);
  init();
  glutIgnoreKeyRepeat(true);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return EXIT_SUCCESS;
}
