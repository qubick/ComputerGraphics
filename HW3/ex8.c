/*
 *  3D Objects
 *
 *  Demonstrates how to draw objects in 3D.
 *
 *  Key bindings:
 *  m/M        Cycle through different sets of objects
 *  a          Toggle axes
 *  arrows     Change view angle
 *  0          Reset view angle
 *  ESC        Exit
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th=15;         //  Azimuth of view angle
int ph=35;         //  Elevation of view angle
double zh=0;      //  Rotation of teapot
int axes=1;       //  Display axes
int mode=0;       //  What to display

int time=0;
//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

#define PI 3.141592653589792384
#define RADIUS 1
/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void sleep(int time)
{
	int i,j=0;

	for(i=0; i<time; i++)
		for(j=0; j<time; j++);

}
/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimentions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void truck(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   double i = 0.0;

   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   
   //  Front
   glBegin(GL_POLYGON);
   glColor3f(1,0,0); //red
   glVertex3f(0,0, 0);
   glVertex3f(10,0, 0);
   glVertex3f(10,4, 0);
   glVertex3f(4,4,0);
   glVertex3f(2,2,0);
   glVertex3f(0,1,0);	
	glEnd();

   //back
	glBegin(GL_POLYGON);
   glColor3f(0,1,0); //green
   glVertex3f(0,0, -4);
   glVertex3f(10,0, -4);
   glVertex3f(10,4, -4);
   glVertex3f(4,4,-4);
   glVertex3f(2,2,-4);
   glVertex3f(0,1,-4);
  	glEnd();

	glBegin(GL_QUADS);

   // right
   glColor3f(0,0,1); //blue
   glVertex3f(10,0,0);
   glVertex3f(10,0,-4);
   glVertex3f(10,4,-4);
   glVertex3f(10,4,0);

	
   // left_bottom
   glColor3f(0,1,0);//green
   glVertex3f(0, 0, 0);
   glVertex3f(0,0,-4);
   glVertex3f(0,1,-4);
   glVertex3f(0,1,0);
  
   //  left_bonnet
   glColor3f(1,1,0); //yellow
   glVertex3f(0,1,0);
   glVertex3f(0,1,-4);
   glVertex3f(2,2,-4);
   glVertex3f(2,2,0);

   //  left_window
   glColor3f(0,1,1); //cyan
   glVertex3f(2,2,0);
   glVertex3f(2,2,-4);
   glVertex3f(4,4,-4);
   glVertex3f(4,4,0);

   //  top
   glColor3f(1,1,1);
   glVertex3f(4,4,0);
   glVertex3f(4,4,-4);
   glVertex3f(10,4,-4);
   glVertex3f(10,4,0);
   
   //  bottom
   glColor3f(1,1,1);
   glVertex3f(0,0,0);
   glVertex3f(0,0,-4);
   glVertex3f(10,0,-4);
   glVertex3f(10,0,0);
 
 	glEnd();

  //*************** Tire front *******************//
	glColor3f(.2, .3, .5);
	glBegin(GL_POLYGON);
	for(i = 0; i<2 * PI; i+= PI/4)
		glVertex3f(cos(i)*RADIUS+3, sin(i)*RADIUS, -.5);
	glEnd();

	glBegin(GL_POLYGON);
	for(i = 0; i<2 * PI; i+= PI/6)
		glVertex3f(cos(i)*RADIUS+8, sin(i)*RADIUS, -.5);
	glEnd();

	//Tire back
	glBegin(GL_POLYGON);
	for(i = 0; i<2 * PI; i+= PI/6)
		glVertex3f(cos(i)*RADIUS+3, sin(i)*RADIUS, -3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
	for(i = 0; i<2 * PI; i+= PI/6)
		glVertex3f(cos(i)*RADIUS+8, sin(i)*RADIUS, -3.5);
	glEnd();
  //********* Side mirro Right********//
	glBegin(GL_QUADS);
	//mirror-front
	glColor3f(1,1,1);
	glVertex3f(5,2,.5);
	glVertex3f(5.3,2,.5);
	glVertex3f(5.3,3,.5);
	glVertex3f(5,3,.5);

	// mirror-left
	glColor3f(1,0,1);
	glVertex3f(5,2,0);
	glVertex3f(5,2,.5);
	glVertex3f(5,3,.5);
	glVertex3f(5,3,0);

	// mirror-right
	glColor3f(1,0,1);
	glVertex3f(5.3,2,0);
	glVertex3f(5.3,2,.5);
	glVertex3f(5.3,3,.5);
	glVertex3f(5.3,3,0);
   
	// mirror-top
	glColor3f(1,0,1);
	glVertex3f(5,2,0);
	glVertex3f(5,2,.5);
	glVertex3f(5.3,2,.5);
	glVertex3f(5.3,2,0);
   
	// mirror-top
	glColor3f(0,1,0);
	glVertex3f(5,3,0);
	glVertex3f(5,3,.5);
	glVertex3f(5.3,3,.5);
	glVertex3f(5.3,3,0);
   
  /********* Side mirro Right********/
	//mirror-front
	glColor3f(1,1,1);
	glVertex3f(5,2,-4.5);
	glVertex3f(5.3,2,-4.5);
	glVertex3f(5.3,3,-4.5);
	glVertex3f(5,3,-4.5);

	// mirror-left
	glColor3f(1,0,1);
	glVertex3f(5,2,-4);
	glVertex3f(5,2,-4.5);
	glVertex3f(5,3,-4.5);
	glVertex3f(5,3,-4);
   

	// mirror-right
	glColor3f(1,0,1);
	glVertex3f(5.3,2,-4);
	glVertex3f(5.3,2,-4.5);
	glVertex3f(5.3,3,-4.5);
	glVertex3f(5.3,3,-4);
   
	// mirror-bottom
	glColor3f(0,1,1);
	glVertex3f(5,2,-4);
	glVertex3f(5,2,-4.5);
	glVertex3f(5.3,2,-4.5);
	glVertex3f(5.3,2,-4);
   
	// mirror-top
	glColor3f(0,1,1);
	glVertex3f(5,3,-4);
	glVertex3f(5,3,-4.5);
	glVertex3f(5.3,3,-4.5);
	glVertex3f(5.3,3,-4);
   //  End
   glEnd();
   
   //  Undo transformations
   glPopMatrix();
}

static void taxi(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   double i = 0.0;

   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   
   //  Front
   glBegin(GL_POLYGON);
   glColor3f(1,0,0); //red
   glVertex3f(0,0, 0);
   glVertex3f(10,0, 0);
   glVertex3f(10,1, 0);
   glVertex3f(9,1,0);
   glVertex3f(8,3,0);
   glVertex3f(4,3,0);	
	glVertex3f(2.5,1,0);
	glVertex3f(0,1,0);
	glEnd();

   // back
   glBegin(GL_POLYGON);
   glColor3f(1,0,-4); //red
   glVertex3f(0,0, -4);
   glVertex3f(10,0, -4);
   glVertex3f(10,1, -4);
   glVertex3f(9,1,-4);
   glVertex3f(8,3,-4);
   glVertex3f(4,3,-4);	
	glVertex3f(2.5,1,-4);
	glVertex3f(0,1,-4);
	glEnd();
	
	glBegin(GL_QUADS);

   // right_bottom
   glColor3f(0,0,1); //blue
   glVertex3f(10,0,0);
   glVertex3f(10,0,-4);
   glVertex3f(10,1,-4);
   glVertex3f(10,1,0);

	//right_window
   glColor3f(0,1,1); //cyan
   glVertex3f(9,1,0);
   glVertex3f(9,1,-4);
   glVertex3f(8,3,-4);
   glVertex3f(8,3,0);

   // left_bottom
   glColor3f(0,1,0);//green
   glVertex3f(0, 0, 0);
   glVertex3f(0,0,-4);
   glVertex3f(0,1,-4);
   glVertex3f(0,1,0);
  
   //  left_window
   glColor3f(1,1,0); //yellow
   glVertex3f(1.5,1,0);
   glVertex3f(1.5,1,-4);
   glVertex3f(4,3,-4);
   glVertex3f(4,3,0);

   //  top
   glColor3f(1,1,1);
   glVertex3f(4,3,0);
   glVertex3f(4,3,-4);
   glVertex3f(8,3,-4);
   glVertex3f(8,3,0);
  
   glColor3f(.5, .2, .2);
   glVertex3f(0,1,0);
   glVertex3f(0,1,-4);
   glVertex3f(2,1,-4);
   glVertex3f(2,1,0);
   
   glColor3f(.3, .3, .2);
   glVertex3f(9,1,0);
   glVertex3f(9,1,-4);
   glVertex3f(10,1,-4);
   glVertex3f(10,1,0);
   //  bottom
   glColor3f(1,1,1);
   glVertex3f(0,0,0);
   glVertex3f(0,0,-4);
   glVertex3f(10,0,-4);
   glVertex3f(10,0,0);

	//********************* cab ************//
	//front
	glColor3f(.1, .7, .7);
	glVertex3f(5,3,-1);
	glVertex3f(6,3,-1);
	glVertex3f(6,4,-1);
	glVertex3f(5,4,-1);
 	
	//back
	glColor3f(.1, .7, .7);
	glVertex3f(5,3,-3);
	glVertex3f(6,3,-3);
	glVertex3f(6,4,-3);
	glVertex3f(5,4,-3);

	//left
	glColor3f(.1, .4, .3);
	glVertex3f(5,3,-1);
	glVertex3f(5,4,-1);
	glVertex3f(5,4,-3);
	glVertex3f(5,3,-3);

	//right
	glColor3f(.1, .4, .3);
	glVertex3f(6,3,-1);
	glVertex3f(6,4,-1);
	glVertex3f(6,4,-3);
	glVertex3f(6,3,-3);
	
	//top
	glColor3f(.9, .2, .2);
	glVertex3f(5,4,-1);
	glVertex3f(6,4,-1);
	glVertex3f(6,4,-3);
	glVertex3f(5,4,-3);
	glEnd();

  //*************** Tire front *******************//
	glColor3f(.2, .3, .5);
	glBegin(GL_POLYGON);
	for(i = 0; i<2 * PI; i+= PI/4)
		glVertex3f(cos(i)*RADIUS+3, sin(i)*RADIUS, -.5);
	glEnd();

	glBegin(GL_POLYGON);
	for(i = 0; i<2 * PI; i+= PI/6)
		glVertex3f(cos(i)*RADIUS+8, sin(i)*RADIUS, -.5);
	glEnd();

	//Tire back
	glBegin(GL_POLYGON);
	for(i = 0; i<2 * PI; i+= PI/6)
		glVertex3f(cos(i)*RADIUS+3, sin(i)*RADIUS, -3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
	for(i = 0; i<2 * PI; i+= PI/6)
		glVertex3f(cos(i)*RADIUS+8, sin(i)*RADIUS, -3.5);
   //  End
   glEnd();
   
   //  Undo transformations
   glPopMatrix();
}
/*
//draw a wine glass
static void glass(double x, double y, double z, //translate offset
				  double dx, double dy, double dz, //scale factor
				  double th)
{
	glPushMatrix();
	
	//translate by x,y,z
	glTranslate(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx, dy. dz);

	glBegin(GL_LINE_LOOP);
	glColor3f(0,1,0);
	
	glVertex3f(2,0,0);
	glVertex3f(4,1,0);
	glVertex3f(5,2,0);

	glVertex3f(4,5,0);
	glVertex3f(0,8,0);
	glVertex3f(6,8,0);
	glVertex3f(6,0,0);
	
	glEnd();
	glPopMatrix();
}
*/

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=1.5;  //  Length of axes
   int i = 0;
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   //  Decide what to draw
   switch (mode)
   {
      //  Draw cubes
      case 1:
         truck(0,0,0 , 0.2,0.2,0.2 , 0);
         //truck(1,0,2 , 0.1,0.1,0.1 , 30);
        // truck(0,1,0 , 0.4,0.3,0.2 , 90);
         break;
      //  Draw spheres
      case 2:
         taxi(0,0,0 , 0.2,0.2,0.2 , 0);
        // taxi(0,0,0 , 0.2,0.2,0.2 , 0);
         //taxi(0,0,0 , 0.2,0.2,0.2 , 0);
        
		// bush(0,0,0,1);
	//	trunk(0,0,0, 1);
		 break;
      case 0:
	  	//	printf("ph: %f\t th: %f\t zh:%f\n", ph, th, zh);
		//road
		glBegin(GL_QUADS);
		 glColor3f(0.3, 0.3, 0.3);
		 glVertex3f(-100, -.1, 0);
		 glVertex3f(100, 	-.1, 0);
		 glVertex3f(100, 	-.1, 2);
		 glVertex3f(-100, -.1, 2);
		
		
		glColor3f(1,1,0);
		for(i=-10; i<100; i++){
			glVertex3f(i,		-.1, 1);
			glVertex3f(i+.7,	-.1, 1);
			glVertex3f(i+.7,	-.1, 1.1);
			glVertex3f(i, 	-.1, 1.1);
		}
		glEnd();

		 truck((zh-120)*0.1,.1,1.5	,.15,.15,.15, 180);
		 taxi(-(zh-120)*0.15,0,.5, 	.1,.1,.1, 0);
		
		 truck(2-(zh-120)*0.1,.1,.1 , .1,.1,.1, 0);
		 taxi(-5+(zh-100)*0.07,.2, 1.5, .1,.1,.1, 180);
		
		sleep(10000);
		truck(10-(zh-120)*0.15,.1,.5,	.1,.1,.1,0);
	break;
      case 3:
         //  Cube
         truck(-1,0,0 , 0.2,0.2,0.2 , 3*zh);
         //  Ball
         //vaxisphere2(0,0,0 , 0.3);
         
		 taxi(Cos(zh), Sin(zh), Cos(zh)*Sin(zh), .1,.1,.1,1 );
         break;
   }
   //  White
   glColor3f(1,1,1);
   //  Draw axes
   if (mode != 0)
   	
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
   Print("Angle=%d,%d",th,ph);
   //  Render the scene
   glFlush();
   //  Make the rendered scene visible
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'm')
      mode = (mode+1)%4;
   else if (ch == 'M')
      mode = (mode+6)%4;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   const double dim=2.5;
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  GLUT calls this toutine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(1000,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Hw3-Jeeeun Kim");
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
