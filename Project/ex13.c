/*
 *  Lighting
 *
 *  Demonstrates basic lighting using a sphere and a cube.
 *
 *  Key bindings:
 *  l          Toggles lighting
 *  a/A        Decrease/increase ambient light
 *  b/B			Toggle light source rotation aze - horizontal/vertical
 *  d/D        Decrease/increase diffuse light
 *  s/S        Decrease/increase specular light
 *  e/E        Decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  F3         Increase light distance gradually from 1 to 5
 *  m          Toggles light movement
 *  []         Lower/rise light
 *  p          Toggles ortogonal/perspective projection
 *  +/-        Change field of view of perspective
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"

int axes=1;       //  Display axes
int mode=0;       //  Projection mode
int move=1;       //  Move light
int th=35;         //  Azimuth of view angle
int ph=35;         //  Elevation of view angle
int zh=0;
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=5.0;   //  Size of world
int view = 0;
int time=0;
int ball_mode = 0;

#define SCALE_FACTOR	0.8
#define PI	3.141592653589792384
#define RADIUS	1
#define offset 0.001

// Light values
int one       =   1;  // Unit value
int distance  =   2;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int lzh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light

void sleep(int time){
	int i,j = 0;
	for(i=0; i<time; i++){
		for(j=0; j<time; j++);
	}
}
static void street()
{
	//      printf("ph: %f\t th: %f\t zh:%f\n", ph, th, zh);
   int i=0;

	//asphalt
	glBegin(GL_QUADS);
   	glColor3f(0.3, 0.3, 0.3);
   	glVertex3f(-100, -.1,-1);
		glVertex3f(100, -.1, -1);
		glVertex3f(100, -.1, 3);
		glVertex3f(-100, -.1, 3);

      //stripes
      glColor3f(1,1,0);
			for(i=-10; i<100; i++){
				glVertex3f(i,           -.1+offset, 1);
				glVertex3f(i+.7,        -.1+offset, 1);
				glVertex3f(i+.7,        -.1+offset, 1.1);
				glVertex3f(i,           -.1+offset, 1.1);
         }
		glEnd();

}
static void box(double x,double y,double z,
                 double dx,double dy,double dz,
					  double th)
{
	double i = 0.0;

   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
	
	//******************** front ****************//
	glBegin(GL_POLYGON);
		glVertex3f(2,0, 0);
		glVertex3f(5,0, 0);
		glVertex3f(5,30, 0);
		glVertex3f(2,30,0);
		glVertex3f(0,28,0);
		glVertex3f(0,2,0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(5,0,0);
		glVertex3f(20,0,0);
		glVertex3f(25,0,0);
		glVertex3f(35,0,0);
		glVertex3f(35,10,0);
		glVertex3f(25,10,0);
		glVertex3f(20,5,0);
		glVertex3f(5,5,0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(35,0,0);
		glVertex3f(38,0,0);
		glVertex3f(40,2,0);
		glVertex3f(40,28,0);
		glVertex3f(38,30,0);
		glVertex3f(35,30,0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(5,25,0);
		glVertex3f(35,25,0);
		glVertex3f(35,30,0);
		glVertex3f(5,30,0);
	glEnd();


	//******************** left ****************//
	glBegin(GL_POLYGON);
		glVertex3f(40,0,-2);
		glVertex3f(40,0,-5);
		glVertex3f(40,30,-5);
		glVertex3f(40,30,-2);
		glVertex3f(40,28,0);
		glVertex3f(40,2,0);
	glEnd();
	
	//******************** right ****************//
	glBegin(GL_POLYGON);
		glVertex3f(0,0,-2);
		glVertex3f(0,0,-5);
		glVertex3f(0,30,-5);
		glVertex3f(0,30,-2);
		glVertex3f(0,28,0);
		glVertex3f(0,2,0);
	glEnd();
	//  Undo transformations
	glPopMatrix();
}


static void truck(double x,double y,double z,
                 double dx,double dy,double dz,
				     double th)
{
	double i = 0.0;

   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	glVertex3f(0,0, 0);
	//***********************  Front *************************//
	glBegin(GL_POLYGON);
		glColor3f(1,0,0); //red
		glVertex3f(10,0, 0);
		glVertex3f(10,4, 0);
		glVertex3f(4,4,0);
		glVertex3f(2,2,0);
		glVertex3f(0,1,0);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	   glVertex3f(5,0,0);
	   glVertex3f(20,0,0);
	   glVertex3f(30,0,0);
	   glVertex3f(35,0,0);
	   glVertex3f(35,10,0);
	   glVertex3f(30,10,0);
	   glVertex3f(20,5,0);
	   glVertex3f(5,5,0);
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
	
	//*************** Tire back ********************//
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
	//  Undo transformation
	glPopMatrix();
}

/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
			if(ball_mode == 0)
				ball(Position[0],Position[1],Position[2]+1 , 0.1);
			else
				ball(Position[2], Position[0], Position[2]+1, 0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
     glDisable(GL_LIGHTING);

   //  Draw scene
   //cube(+1,0,0 , 0.5,0.5,0.5 , 0);
  // ball(-1,0,-2 , 0.5);

	street();
//   truck(-5+(zh-12)*0.1,.1,1.5,	.15,.15,.15, 180);
//	truck(2-(zh-120)*0.1,.1,.1,    .1,.1,.1, 0);
	
//	taxi(-5+(zh-100)*0.07,.2,1.5, .1,.1,.1, 180);
	box(0,0,0,              .2,.2,.2, 0);
	
//	sleep(10000);
//	truck(10-(zh-120)*0.15,.1,.5,   .1,.1,.1, 0);

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   else if (key == GLUT_KEY_F3){
   	distance++;
		if (distance ==5)
			distance=1;
	}
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode?fov:0,asp,dim);
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
	else if (ch == 'b' || ch == 'B')
		ball_mode = 1-ball_mode;
	//  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P')
      mode = 1-mode;
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Translate shininess power to value (-1 => 0)
   shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(900,600);
   glutCreateWindow("HW5_JeeeunKim_Lighting");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
