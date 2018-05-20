#include <epoxy/gl.h>
#include <gtk/gtk.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "libtarga.h"
#include <locale.h>

const GLchar *vert_src = R"(
#version 330
#extension GL_ARB_explicit_uniform_location : enable
out vec2 kn;
layout(location = 1) in vec2 in_p; // texture
layout(location = 0) in vec4 in_position; // cube vertexes
layout(location =10)uniform mat4 projection; // how cube will be viewed
void main()
{
	gl_Position = projection*in_position;
	kn=in_p ;
//	gl_Position = in_position;
}
)";
const GLchar *frag_src =R"(
#version 330
#extension GL_ARB_explicit_uniform_location : enable
layout(location =11)uniform sampler2D t;
vec4 b;
in vec2 kn;
void main (void)
{
	if(gl_FrontFacing)
	gl_FragColor = texture( t, kn);
	else discard;
}
)";

glm::mat4 yt,b;
GLubyte  *trr;
GLuint gl_vao, gl_buffer, gl_program;
GLuint vertexT,tpr,tpra;
static gboolean realise(GtkGLArea *area, GdkGLContext *context)
{
	gtk_gl_area_make_current(GTK_GL_AREA(area));
	if (gtk_gl_area_get_error (GTK_GL_AREA(area)) != NULL) 
	{
		printf("failed to initialiize buffers\n");
		return false;
	}
/* triangles inside texture , later it cover cube triangles
	GLfloat t[] =
	{
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		0.0, 0.0,

		1.0, 1.0,

		1.0, 1.0,
		0.0, 0.0,
		0.0, 1.0,

		0.0, 0.0,
		1.0, 1.0,
		1.0, 0.0,

		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,

		1.0, 0.0,
		0.0, 0.0,
		1.0, 1.0,

		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		0.0, 0.0,
		1.0, 1.0,

		1.0, 0.0,
		0.0, 0.0,
		1.0, 1.0,

		1.0, 1.0,
		0.0, 0.0,
		0.0, 1.0,

		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,

		1.0, 0.0,
		0.0, 0.0,
		1.0, 1.0
	};

	GLfloat verts[] =
	{
		+0.7, +0.7, +0.7,
		-0.7, 0.7, 0.7,
		-0.7, +0.7, -0.7,

		0.7, +0.7, -0.7,
		+0.7, +0.7, +0.7,
		-0.7, +0.7, -0.7,

		-0.7, -0.7, +0.7,
		+0.7, +0.7, +0.7,
		-0.7, 0.7, 0.7,

		+0.7, +0.7, +0.7,
		-0.7, -0.7, +0.7,
		0.7, -0.7, 0.7,

		+0.7, -0.7, -0.7,
		-0.7, -0.7, -0.7,
		0.7, +0.7, -0.7,

		-0.7, +0.7, -0.7,
		0.7, +0.7, -0.7,
		-0.7, -0.7, -0.7,

		-0.7, -0.7, +0.7,
		-0.7, -0.7, -0.7,
		0.7, -0.7, 0.7,

		+0.7, -0.7, -0.7,
		0.7, -0.7, 0.7,
		-0.7, -0.7, -0.7,

		0.7, +0.7, -0.7,
		+0.7, +0.7, +0.7,
		+0.7, -0.7, -0.7,

		0.7, -0.7, -0.7,
		+0.7, +0.7, +0.7,
		0.7, -0.7, 0.7,

		-0.7, -0.7, -0.7,
		-0.7, 0.7, 0.7,
		-0.7, +0.7, -0.7,

		-0.7, -0.7, +0.7,
		-0.7, 0.7, 0.7,
		-0.7, -0.7, -0.7
	};
	b=glm::lookAt(glm::vec3(1.75,-2.38,1.4444), glm::vec3( 0., 0., 0.),glm::vec3( 0.,0.2,-00.));
	yt=glm::perspective(45., 1., 1.2, 300.);
	b=yt*b*glm::mat4(1.);
	
	unsigned char* targaimage;
	int wdt=512, hgt=512;
	trr = (unsigned char*)tga_load("161208ap5410_fpx.tga", &wdt, &hgt, TGA_TRUECOLOR_32);

	GLuint frag_shader, vert_shader;
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	vert_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(frag_shader, 1, &frag_src, NULL);
	glShaderSource(vert_shader, 1, &vert_src, NULL);

	glCompileShader(frag_shader);
	glCompileShader(vert_shader);

	gl_program = glCreateProgram();
	glAttachShader(gl_program, frag_shader);
	glAttachShader(gl_program, vert_shader);
	glLinkProgram(gl_program);
	glGenVertexArrays(1, &gl_vao);
	glBindVertexArray(gl_vao);

	glGenBuffers(1, &gl_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, gl_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &tpr);
	glBindBuffer(GL_ARRAY_BUFFER,tpr );

	glBufferData(GL_ARRAY_BUFFER, sizeof(t), t, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);

	//glGenTextures(1, &vertexT);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexT);
	//    glActiveTexture(GL_TEXTURE0);
	//    glBindTexture(GL_TEXTURE_2D, vertexT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA,  GL_UNSIGNED_BYTE,trr);

	return TRUE;
}

static gboolean render(GtkGLArea *area, GdkGLContext *context) 
{
	glUseProgram(gl_program);
	glUniformMatrix4fv(10, 1, 0, &b[0][0]);
	glUniform1i(11, 0);
	glBindVertexArray(gl_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
	glFlush();

	return TRUE;
}

int main(int argc, char** argv) {
	gtk_init(&argc, &argv);
	
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL),
	*gl_area = gtk_gl_area_new();

	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(gl_area, "realize", G_CALLBACK(realise), NULL);
	g_signal_connect(gl_area, "render", G_CALLBACK(render), NULL);

	gtk_container_add(GTK_CONTAINER(window), gl_area);
	gtk_widget_show_all(window);
	
	gtk_main();

	return 0;
}
