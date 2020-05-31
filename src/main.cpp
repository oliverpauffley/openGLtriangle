// Hello Triangle
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>

#include <cstdio>

#include "bcm_host.h"

#define TRUE 1
#define FALSE 0

typedef struct {
	// save a Handle to a program object.
	GLuint programObject;

} UserData;

typedef struct Target_State {
	uint32_t width;
	uint32_t height;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;

	EGL_DISPMANX_WINDOW_T nativewindow;
	UserData* user_data;
	void (*draw_func)(struct Target_State*);

} Target_State;

Target_State state;
Target_State* p_state = &state;

static const EGLint attribute_list[] = {EGL_RED_SIZE,	  8,
					EGL_GREEN_SIZE,	  8,
					EGL_BLUE_SIZE,	  8,
					EGL_ALPHA_SIZE,	  8,
					EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
					EGL_NONE};

static const EGLint context_attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
					    EGL_NONE};

// Now we have to be able to create a shader object, pass the shader source and
// the compile the shader.
GLuint LoadShader(GLenum type, const char* shaderSrc) {
	// 1st create the shader object.
	GLuint TheShader = glCreateShader(type);

	if (TheShader == 0) return 0;  // Can't allocate so stop.
	// pas the shader source.
	glCompileShader(TheShader);

	GLint IsItCompiled;

	// After the compile we need to check the status and repot any errors.
	glGetShaderiv(TheShader, GL_COMPILE_STATUS, &IsItCompiled);
	if (!IsItCompiled) {
		GLint RetinfoLen = 0;
		glGetShaderiv(TheShader, GL_INFO_LOG_LENGTH, &RetinfoLen);
		if (RetinfoLen > 1) {
			// standard output for errors
			char* infoLog =
			    (char*)malloc(sizeof(char) * RetinfoLen);
			glGetShaderInfoLog(TheShader, RetinfoLen, NULL,
					   infoLog);
			fprintf(stderr, "Error  compiling this shader:\n%s\n",
				infoLog);
			free(infoLog);
		}
		glDeleteShader(TheShader);
		return 0;
	}
	return TheShader;
}

// Initialize the shader and program object.
int Init(Target_State* p_state) {
	p_state->user_data = (UserData*)malloc(sizeof(UserData));
	GLbyte vShaderStr[] =
	    "attribute vec4 a_position;\n"
	    "attribute vec2 a_texCoord;\n"
	    "varying vec2 v_texCoord;\n"
	    "void main()\n"
	    "{gl_Position=a_position;\n"
	    " v_texCoord=a_texCoord;}\n";

	GLbyte fShaderStr[] =
	    "precision mediump float;\n"
	    "varying vec2 v_texCoord;\n" 
	"uniform sampler2D s_texture;\n"
	    "void main()\n"
	    "{gl_FragColor=vec4 (1.0, 0.0, 0.0, 1.0);}\n";

	GLuint programObject, vertextShader,
	    fragmentShader;  // we need some variables.

	// Load and compile the vertext/fragment shaders
	vertextShader = LoadShader(GL_VERTEX_SHADER, (char*)vShaderStr);
	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, (char*)fShaderStr);

	// Create the program object.
	programObject = glCreateProgram();
	if (programObject == 0) return 0;

	// Attach the V and F shaders to the program object.
	glAttachShader(programObject, vertextShader);
	glAttachShader(programObject, fragmentShader);

	// Link the program.
	glLinkProgram(programObject);
	// Check link status
	GLint AreTheyLinked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &AreTheyLinked);
	if (!AreTheyLinked) {
		GLint RetinfoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &RetinfoLen);
		if (RetinfoLen > 1) {
			GLchar* infoLog =
			    (GLchar*)malloc(sizeof(char) * RetinfoLen);
			glGetProgramInfoLog(programObject, RetinfoLen, NULL,
					    infoLog);
			fprintf(stderr, "Error linking program: \n%s\n",
				infoLog);
			free(infoLog);
		}
		glDeleteProgram(programObject);
		return FALSE;
	}

	// store programObject
	p_state->user_data->programObject = programObject;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	return TRUE;
}

void init_ogl(Target_State* state, int width, int height) {
	int32_t success = 0;
	EGLBoolean result;
	EGLint num_config;
	// RPI setup
	DISPMANX_ELEMENT_HANDLE_T DispmanElementH;
	DISPMANX_DISPLAY_HANDLE_T DispmanDisplayH;
	DISPMANX_UPDATE_HANDLE_T DispmanUpdateH;
	VC_RECT_T dest_rect;
	VC_RECT_T src_rect;

	EGLConfig config;

	// Get an EGL display connection
	state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	// initialize the connection
	result = eglInitialize(state->display, NULL, NULL);

	// Get an appropriate EGL frame buffer config.
	result = eglChooseConfig(state->display, attribute_list, &config, 1,
				 &num_config);
	assert(EGL_FALSE != result);

	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(EGL_FALSE != result);

	// Create egl rendering context
	state->context = eglCreateContext(state->display, config,
					  EGL_NO_CONTEXT, context_attributes);
	assert(state->context != EGL_NO_CONTEXT);

	// Create an EGL window surface
	state->width = width;
	state->height = height;

	dest_rect.x = 0;
	dest_rect.y = 0;
	dest_rect.width = state->width;
	dest_rect.height = state->height;

	src_rect.x = 0;
	src_rect.y = 0;

	DispmanDisplayH = vc_dispmanx_display_open(0);
	DispmanUpdateH = vc_dispmanx_update_start(0);

	DispmanElementH = vc_dispmanx_element_add(
	    DispmanUpdateH, DispmanDisplayH, 0 /*layer*/, &dest_rect,
	    0 /*source*/, &src_rect, DISPMANX_PROTECTION_NONE,
	    0 /*alpha value*/, 0 /*clamp*/,
	    (DISPMANX_TRANSFORM_T)0 /*transform*/);
	state->nativewindow.element = DispmanElementH;
	state->nativewindow.width = state->width;
	state->nativewindow.height = state->height;
	vc_dispmanx_update_submit_sync(DispmanUpdateH);
	state->surface = eglCreateWindowSurface(state->display, config,
						&(state->nativewindow), NULL);
	assert(state->surface != EGL_NO_SURFACE);
	// connect the context to the surface
	result = eglMakeCurrent(state->display, state->surface, state->surface,
				state->context);
	assert(result != EGL_FALSE);
}

/*
 * Draw a triangle
 * This is only good for this hardcoded example
 */
void Draw(Target_State* p_state) {
	UserData* userData = p_state->user_data;
	GLfloat TriVertices[] = {0.0f, 0.5f, 0.0f,  -0.5f, -0.5f,
				 0.0f, 0.5f, -0.5f, 0.0f};

	// Setup viewport
	glViewport(0, 0, p_state->width, p_state->height);

	// Clear the colour buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Use the programObject
	glUseProgram(userData->programObject);

	// Load the vertext data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, TriVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	if (glGetError() != GL_NO_ERROR) printf("Oh bugger");
}

void esInitContext(Target_State* p_state) {
	if (p_state != NULL) {
		memset(p_state, 0, sizeof(Target_State));
	}
}

void esRegisterDrawFunc(Target_State* p_state,
			void (*draw_func)(Target_State*)) {
	p_state->draw_func = draw_func;
}
void esMainLoop(Target_State* esContext) {
	int Counter = 0;  // keep a counter
	while (Counter++ < 200) {
		if (esContext->draw_func != NULL)
			esContext->draw_func(esContext);
		// After our draw we need to swap buffers to display
		eglSwapBuffers(esContext->display, esContext->surface);
	}
}

int main(int argc, char* argv[]) {
	UserData user_data;
	bcm_host_init();  // RPI needs this
	esInitContext(p_state);
	init_ogl(p_state, 1024, 720);
	p_state->user_data = &user_data;

	if (!Init(p_state)) return 0;
	esRegisterDrawFunc(p_state, Draw);
	// Now do graphic loop
	esMainLoop(p_state);
}
