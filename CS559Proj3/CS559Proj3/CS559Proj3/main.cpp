//Oh god what is this I don't even

#include <sstream>
#include <string>
#include <iostream>
#include <math.h>

#include "physicsInclude.h"
#include "glutInclude.h"

#include "DrawObject.h"
#include "World.h"
#include "Camera.h"
#include "Cube.h"
#include "Textures.h"
#include "FrameBufferObject.h"
#include "ShadowFBO.h"
#include "ShaderWithShadows.h"
#include "GoochShader.h"
#include "FireShader.h"
#include "Axes.h"
#include "Sphere.h"
#include "Cursor.h"

#ifdef _DEBUG
	#define CRTDBG_MAP_ALLOC //Used to help find leaks.
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

bool wireframe = false; // Determine if we want wireframe.
float fov = 50.0f; // Our FOV.
//float radius = 5.0f; // Distance away from our eye.
int animFrame = 0; // Used to make it rain.
//bool doRain = FALSE; // Are we making it rain?
bool drawGrid = FALSE; // Are we showing the grid?

Shader DrawObject::norm_shader; // Shared shader for normals.
DrawObject * DrawObject::a; // Shared object used to draw axes.

bool DrawObject::draw_norms; // Boolean to declare if we want to draw normals.
bool DrawObject::draw_axes; // Boolean to declare if we want to draw local axes.
bool DrawObject::axes_init; // Boolean to determine if the shared Axes object is initialized.
Shader * common_shader; //Shader shared amongst standard DrawObjects (here, spheres)


int Shader::bind_point = 2; // Bindings for our lighting/materials.

int mouseX = -1; //Lets us smoothly adjust our view.
int mouseY = -1;

GLint Shader::light_index = GLuint(-1);
GLuint Shader::light_handle = GLuint(-1); // Used in our lighting calcs

GLuint tex[NUM_TEXTS]; //Used for setting up texturing

World draw_world; //Where we actually draw/simulate everything
Player * game_player; //Our player in the world

int num_spheres; //Number of spheres in the world
float max_time; //Total time
float elapsed_time; //Time elapsed in game world

static bool msaa_on = false; //Lets us toggle MSAA

FrameBufferObject fbo; //For drawing jumbotron
ShadowFBO s_fbo; //For drawing shadows

//For dynamic shadows
glm::mat4 light_matrix; //Light's POV, used in dynamic shadows
glm::mat4 bp_matrix; //Bias times light's projection matrix

GLubyte * noise3DTexPtr; //Memory where we write our noise texture
const int NOISE_RES = 128; //Resolution for our noise texture
GLuint noise_tex_handle; //Texture handle for noise

freetype::font_data draw_font; //Would have been used to draw numbers above spheres
freetype::font_data info_font; //Would have been used to draw game info

b2Vec2 player_pos; //Location of player in world; ultimately unused

Axes common_axes; //For drawing local axes
const int NUM_SHADERS = 4; //Total number of shaders
Shader * global_shaders[NUM_SHADERS]; //TEX_W_SHADOWS, GOOCH, FIRE_NOISE, NOISE_NORMAL
int global_shader_id = 0; //Lets us cycle through shaders
Window window; //Our window, shockingly.

bool fatal_error = false; //Used to note we had a fatal error

Cursor cursor;

// This function taken from DevIL documentation.
// http://openil.sourceforge.net/tuts/tut_3/index.htm
void getDevILErr()
{
	ILenum Error;
	while ((Error = ilGetError()) != IL_NO_ERROR) {
		printf("%d: %s/n", Error, iluErrorString(Error));
	} 
}

//Cleanly exit the program
void ExitFunc(void)
{
	glutLeaveMainLoop();
	if (fatal_error)
	{
		fprintf(stderr, "A fatal error occured.  Exiting...\n");
	}
	draw_world.TakeDown();
	fbo.TakeDown();

	s_fbo.TakeDown();
	if (common_shader != NULL)
	{
		common_shader->TakeDown();
	}

	glDeleteTextures(NUM_TEXTS, tex);
	glDeleteTextures(1, &noise_tex_handle);
	if (noise3DTexPtr) 
	{
		free(noise3DTexPtr);	
	}

	glutExit();
	
	if(!fatal_error)
	{
		printf("Time elapsed: %f\n", elapsed_time/10000);
		if (WON_GAME) { printf("Congrats! You won!\n"); }
		else { printf("Sorry, you lose.\n"); }
	}
	
	system ("PAUSE");

	//Look for any lingering exceptions
	try
	{
	exit(0);
	}catch (std::exception &e) {
		printf(e.what());
	}
}


//This method adapted from "OpenGL Shading Language, Third Edition" by Randi J. Rost and Bill Licea-Kane.
bool makeNoiseTexture(void)
{
	//count_down_timer_seconds = 30 +numballs*2
#ifdef _DEBUG
	return true;
#endif

	int f, i, j, k, inc; //Loop variables
	int startFrequency = 4; //Initial frequency
	int numOctaves = 4; //Number of octaves we will generate/sum
	double inci, incj, inck; //Summation variables
	noise::module::Perlin perlinNoise; //Our perlin noise generator

	int frequency = startFrequency;
	GLubyte * ptr; //Use to walk through our texture in memory
	double amp = 0.5; //Amplitude we'll use
	if (!(noise3DTexPtr = (GLubyte *) malloc(NOISE_RES * NOISE_RES * NOISE_RES * 4)))
	{
		fprintf(stderr, "Could not allocate memory for noise!\n");
		fatal_error = true;
		ExitFunc();
	}

	for (f = 0, inc = 0; f < numOctaves; f++, inc++)
	{
		perlinNoise.SetFrequency(frequency);
		ptr = noise3DTexPtr;

		inci = 1.0 / (NOISE_RES / frequency);
		for (i = 0; i < NOISE_RES; i++)
		{
			incj = 1.0 / (NOISE_RES / frequency);
			for (j = 0; j < NOISE_RES; j++)
			{
				inck = 1.0 / (NOISE_RES / frequency);
				for (k = 0; k < NOISE_RES; k++)
				{
					*(ptr + inc) = (GLubyte) (perlinNoise.GetValue(inci * i, incj * j, inck * k) * NOISE_RES * amp); //Sample our noise
					ptr += 4;
				}
			}
		}
		frequency *= 2;
		amp *= 0.5; //Adjust the frequency/amplitude to get different octaves
	}

	glGenTextures(1, &noise_tex_handle);
	glBindTexture(GL_TEXTURE_3D, noise_tex_handle);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, NOISE_RES, NOISE_RES, NOISE_RES, 0, GL_RGBA, GL_UNSIGNED_BYTE, noise3DTexPtr);
	return true;
}


void initTextures()
{
	//Initialize external textures
	GLuint tid[NUM_TEXTS];
	int i = 0;
	for (i = 0; i < NUM_TEXTS; i++)
	{
		if (texts[i] == NULL) { break; }
		ilGenImages(1, &tex[i]); // Set up texture handle.
		ilBindImage(tex[i]);
	
		//Below code is also taken from the DevIL documentation.
		//We read the file into memory, then use DevIL to bind it
		//as a texture.
		ILubyte *Lump;
		ILuint Size;
		FILE *File;

		int err = fopen_s(&File, texts[i], "rb");
		if (err)
		{
			fprintf(stderr, "Error: Could not open texture %s\n", texts[i]);
			fatal_error = true;
			ExitFunc();
		}
		fseek(File, 0, SEEK_END);
		Size = ftell(File);

		Lump = (ILubyte*)malloc(Size);
		fseek(File, 0, SEEK_SET);
		fread(Lump, 1, Size, File);
		fclose(File);

		if (!ilLoadL(IL_JPG, Lump, Size)) { getDevILErr(); exit(1); }
		free(Lump);

		glActiveTexture((GL_TEXTURE0 + i));
		glGenTextures(1, &tid[i]);
		glBindTexture(GL_TEXTURE_2D, tid[i]);
		int w = ilGetInteger(IL_IMAGE_WIDTH);
		int h = ilGetInteger(IL_IMAGE_HEIGHT);
		void * data = ilGetData();
		ilutGLBindTexImage();
		

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	//Initialize FBO
	glActiveTexture(GL_TEXTURE0 + int(FRAME_BUF));
	fbo.initialize(glm::ivec2(512, 512), 1, true);
	//Initialize FBO for dynamic shadows
	glActiveTexture(GL_TEXTURE0 + int(SHADOW_BUF));
	s_fbo.initialize();
	//Initialize noise texture
	glActiveTexture(GL_TEXTURE0 + int(NOISE));
	makeNoiseTexture();
}

void cycleShaders()
{
	//Cycle through our shaders
	global_shader_id++;
	global_shader_id %= NUM_SHADERS;
	common_shader = global_shaders[global_shader_id];
	render_shader = RENDER_SHADER(global_shader_id);
	if (render_shader == TEX_SHADER)
	{
		draw_world.switchFloorShader(false);
	}
	else
	{
		draw_world.switchFloorShader(true);
	}
}

void initShaders()
{
	//Init main shaders
	global_shaders[0] = new ShaderWithShadows();
	global_shaders[0]->init(TEX_W_SHADOWS);
	global_shaders[1] = new GoochShader();
	global_shaders[1]->init(GOOCH);
	global_shaders[2] = new FireShader();
	global_shaders[2]->init(FIRE_NOISE);
	global_shaders[3] = new FireShader();
	global_shaders[3]->init(NOISE_NORMAL);
}


void PassiveMotionFunc(int x, int y)
{
	//Adjust our angle/speed
	if (is_paused) return;
	else
	{
		float ang_ratio = (x - (float)window.width/2)/((float)window.width/2);
		float speed_ratio = (((float)window.height/2) - y)/((float)window.height/2);
		game_player->setSpeed(degToRad(90.0f) * ang_ratio, 60.0f * speed_ratio);
		printf("ang_ratio: %f, speed_ratio: %f\n", ang_ratio, speed_ratio);
	}
}

void showInfo()
{
	//Print out game info
	    glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glColor3f(1.0f, 1.0f, 1.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window.width, 0, window.height, 1, 10);
        glViewport(0, 0, window.width, window.height);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(10, 15 * 2, -5.5);
        glScaled(0.1, 0.1, 1.0);
        glPushMatrix();

		char infoString[50];
		sprintf_s(infoString, "Time elapsed: %.3fs,\nspheres remaining: %i", elapsed_time/1000, num_spheres);
        glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *) infoString);


        glPopMatrix();
}

void RenderScene(bool do_physics, int draw_width, int draw_height)
{
	if (num_spheres == 0) { WON_GAME = true; }
	
	float current_time = float(glutGet(GLUT_ELAPSED_TIME));
#ifdef _DEBUG
	printf("current_time: %f\n",current_time);
	printf("elapsed_time: %f\n",elapsed_time);
#endif

	//Set up basic flags
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, draw_width, draw_height);

	glDepthFunc(GL_LESS);

	if (msaa_on)
	{
		//Use GL's legacy MSAA; unfortunately not supported on Cyclops machines
		glEnable(GL_MULTISAMPLE_ARB);
	}
	else
	{
		glDisable(GL_MULTISAMPLE_ARB);
	}
	if (render_target == RENDER_SFBO) {
		//Cull front faces and enable polygon offset to avoid shadow artifacting
		glCullFace(GL_FRONT);
		glPolygonMode(GL_BACK, GL_FILL);
		glPolygonOffset(1.5f, 1.0f);
	}
	if (render_shader == GOOCH_SHADER)
	{
		//Part of gooch shading; we first render a thick black wireframe on the back faces only
		//in order to cheaply get a 'border' effect.
		RENDER_TARGET old_target = render_target;
		render_target = RENDER_GOOCH;
		glLineWidth(5.0);
		glPolygonMode(GL_BACK, GL_LINE);
		glDepthFunc(GL_LEQUAL);
		glCullFace(GL_FRONT);
		draw_world.draw(false);
		glLineWidth(1.0);
		glDepthFunc(GL_LESS);
		glCullFace(GL_BACK);
		render_target = old_target;
	}
	if (wireframe) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	//Do our main render
	draw_world.draw(do_physics);

	if (render_target == RENDER_SFBO) {
		//Reset values
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonOffset(1.0f, 1.0f);
	}

	if (render_target == RENDER_FULL)
	{
		//Draw crosshair

	    glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glColor3f(1.0f, 1.0f, 1.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window.width, 0, window.height, 1, 10);
        glViewport(0, 0, window.width, window.height);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		glLineWidth(1.0);
		glBegin(GL_LINES);
		//For boring crosshair
		glVertex2f(-0.03f, 0);
		glVertex2f( 0.03f, 0);
		glVertex2f(0,-0.03f*window.aspect);
		glVertex2f(0, 0.03f*window.aspect);
		//For Tilted one
		glVertex2f(-0.02f,-0.02f*window.aspect);
		glVertex2f( 0.02f, 0.02f*window.aspect);
		glVertex2f(-0.02f, 0.02f*window.aspect);
		glVertex2f( 0.02f,-0.02f*window.aspect);
		//glVertex2f(0,-0.03f*window.aspect);
		//glVertex2f(0, 0.03f*window.aspect);
		glEnd();

		glPopMatrix();
		showInfo();

	}
	glFlush();
}

void DisplayFunc()
{
	//Do our necessary rendering
	if (fatal_error) ExitFunc();
	if (is_paused) return;
	if (useShadows && (render_shader == TEX_SHADER))
	{
		s_fbo.bind(0);
		render_target = RENDER_SFBO;
		RenderScene(false, SHADOW_BUFFER_RES, SHADOW_BUFFER_RES); //Render to shadow map
		s_fbo.unbind();
	}

	fbo.bind(0);
	render_target = RENDER_FBO;
	RenderScene(false, 512, 512); //Render to framebuffer
	fbo.unbind();
	render_target = RENDER_FULL;
	RenderScene(true, window.width, window.height);
}

void timerFunc(int value)
{
	if (window.handle!= -1)
	{
		glutTimerFunc(window.interval, timerFunc, value);
		if (!is_paused)
		{
			//Leftover code for animation that's unused
			//animFrame++;
			//if (animFrame > 200) animFrame = 0;
			elapsed_time += window.interval;
			glutPostRedisplay();
		}
	}
}

void KeyboardFunc(unsigned char c, int x, int y)
{
	if (c == 'a')
	{
		//Draw local axes
		DrawObject::draw_axes = !DrawObject::draw_axes;
	}
	if (c == 'c')
	{
		//Toggle birds-eye
		draw_world.switchCam();
	}
	if (c == 'p')
	{
		//Need to pause/unpause
		if (is_paused)
		{
			is_paused = false;
			glutPassiveMotionFunc(PassiveMotionFunc);
		}
		else
		{
			is_paused = true;
			glutPassiveMotionFunc(NULL);
		}
	}
	if (c == 's')
	{
		//Toggle shadows
		useShadows = !useShadows;
	}
	if (c == 'w')
	{
		//Toggle wireframe
		wireframe = !wireframe;
	}
	if (c == 'x')
	{
		//End game
		ExitFunc();
	}
	if (c == 'm')
	{
		//Toggles GLUT's MSAA - which unfortunately isn't supported on Cyclops machines
		msaa_on = !msaa_on;
	}
	if (c == 'n')
	{
		//Draw normals
		DrawObject::draw_norms = !DrawObject::draw_norms;
	}
}

void ReshapeFunc(int w, int h)
{
	//Reshape our window
	if (w > 0 && h > 0 && window.handle != -1)
	{
		window.width = w;
		window.height = h;
		window.aspect = (float) w/ (float) h;
	}
}

void SpecialFunc(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_F2:
#ifdef _DEBUG
		printf("Adjusting skybox!\n");
#endif
		//Switch skybox
		draw_world.switchSkydome();
		break;
	case GLUT_KEY_F3:
		//Switch shaders
		cycleShaders();
		break;
	default:
		break;
	}
}

int main (int argc, char * argv[])
{

#ifdef _DEBUG
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	
	//Set up command line args
	int rand_seed;

	if (argc <= 1)
	{
		num_spheres = 30;
		rand_seed = 0;
	}
	else if (argc == 2)
	{
		num_spheres = atoi(argv[1]);
		rand_seed = 0;
	}
	else if (argc == 3)
	{
		num_spheres = atoi(argv[1]);
		rand_seed = atoi(argv[2]);
	}
	else
	{
		fprintf(stderr, "Usage: 559Proj3 numspheres randseed\n");
		exit(1);
	}
	srand(rand_seed);
	max_time = (float)(30 + num_spheres * 2);
	
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	window.width = 800;
	window.height = 600;
	window.aspect = (float) 800/ (float)600;
	window.handle = glutCreateWindow("Moshball");
	
	//Attempt to use FreeType
	draw_font.init("Test.TTF", 40);
	info_font.init("COURIER.TTF", 20);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, window.width, window.height);
	glRasterPos2i(0, 0);
	glPushMatrix();
	const unsigned char load_msg[] = "Loading..."; //Create load screen
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, load_msg);
//	freetype::print(info_font, window.width - 50, window.height - 50, "freeType test");
	
	glPopMatrix();
	glFlush();

	GLenum err = glewInit();

	if ( err != GLEW_OK )
	{
		fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
		exit(1);
	}

	GLEW_IS_INIT = true;
	
	//Init DevIL
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);

	initTextures();
	initShaders();
	common_shader = global_shaders[0];
	
	//Init game world
	draw_world.init(num_spheres);
	game_player = draw_world.getPlayer();
	DrawObject::axes_init = common_axes.init();
	DrawObject::a = &common_axes;
	DrawObject::norm_shader.init(NORM);
	
	draw_world.switchFloorShader(false);

	glutDisplayFunc(DisplayFunc);
	glutTimerFunc(window.interval, timerFunc, 0);
	glutKeyboardFunc(KeyboardFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);
	glutReshapeFunc(ReshapeFunc);
	glutSpecialFunc(SpecialFunc);
	glutMainLoop();

	ExitFunc();


	return 0;
}