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
 out  vec2 kn; 
out  vec4 knn;
                                                   
           layout(location = 1) in vec2 in_p;                                       
           layout(location = 0) in vec4 in_position;                                       
           layout(location =10)uniform  mat4 projection;
           layout(location =2)in vec3 n;
out  vec3 cb;
out  mat4 p;
void main()                                   
{
	

p= projection;
cb=n;
  gl_Position =  projection*in_position;  
kn=in_p  ;
knn=in_position;  
//  gl_Position =  in_position;  
}                                  
)";

const GLchar *frag_src =R"(
#version 330                                  
	#extension GL_ARB_explicit_uniform_location : enable               
layout(location =11)uniform sampler2D t;
                                                  
 float intensity;             
    in  vec2 kn;
    in  vec4 knn;
in  mat4 p;
          in vec3 cb;
          layout(location =13)uniform  mat4 pro;
          layout(location =14)uniform  mat4 tw;

void main()                              
{
vec3 b=vec3(5.5,-.4,-.42);

vec4 h = normalize(tw*vec4(cb,0.0));
vec3 s = vec3(pro * knn );
vec3 hk=normalize(b - s);
intensity = max(dot(h.xyz,hk), 0.0);
 if(gl_FrontFacing)                                
  gl_FragColor = vec4( intensity*texture( t, kn).xyz, 1.);                   
else  discard; 
}                                            
)";



int bba;

glm::mat4 yt,b,bc,bct;



GLuint gl_vao, gl_buffer, gl_program;
GLuint vertexT,tpr,tpra;
static gboolean realise(GtkGLArea *area, GdkGLContext *context)
{
GLubyte  *trr;

  gtk_gl_area_make_current(GTK_GL_AREA(area));
GLfloat t[1728]; 

GLfloat ttk[1727];

GLfloat verts[1727];
char wq[150],wk[150];
 FILE *w=fopen("Untitled.obj","r");
 FILE *ww=fopen("Untitled.obj","r");
do
fscanf(w,"%s",wq);
while(wq[0]!='v');
int pv=ftell(w)-1;

do
fscanf(w,"%s",wq);
while(wq[1]!='n');
int pvc=ftell(w)-2;

do
fscanf(w,"%s",wq);
while(wq[1]!='t');
int pvt=ftell(w)-2;

do
fscanf(w,"%s",wq);
while(wq[0]!='f');
fseek(w,-1,SEEK_CUR);


int bbh=0;
int bbp=0;

int bbr,bbu,bbw,ab,abu,abw,cbr,cbu,cbw;
setlocale(LC_NUMERIC, "C");


do
{
fscanf(w,"%[^\n]%*c",wq);
if(feof(w)) break;
sscanf(wq,"f %d/%d/%d %d/%d/%d %d/%d/%d ", &bbr,&bbu,&bbw,&ab,&abu,&abw,&cbr,&cbu,&cbw);

fseek(ww,pv,SEEK_SET);
for(int c=0;c<bbr;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(wq,"v %f %f %f",&verts[bbh],&verts[bbh+1],&verts[bbh+2]);

fseek(ww,pvt,SEEK_SET);
for(int c=0;c<bbu;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(wq,"vt %f %f",&t[bbp],&t[bbp+1]);

fseek(ww,pvc,SEEK_SET);
for(int c=0;c<bbw;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(wq,"vn %f %f %f",  &ttk[bbh],  &ttk[bbh+1],  &ttk[bbh+2]);
bbh+=3;
bbp+=2;

fseek(ww,pv,SEEK_SET);
for(int c=0;c<ab ;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(wq,"v %f %f %f",&verts[bbh],&verts[bbh+1],&verts[bbh+2]);

fseek(ww,pvt,SEEK_SET);
for(int c=0;c<abu;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(wq,"vt %f %f", &t[bbp],&t[bbp+1]);


fseek(ww,pvc,SEEK_SET);
for(int c=0;c<abw;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(wq,"vn %f %f %f",  &ttk[bbh],  &ttk[bbh+1],  &ttk[bbh+2]);

bbh+=3;
bbp+=2;

fseek(ww,pv,SEEK_SET);
for(int c=0;c<cbr;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(wq,"v %f %f %f" ,&verts[bbh],&verts[bbh+1],&verts[bbh+2]);


fseek(ww,pvt,SEEK_SET);
for(int c=0;c<cbu;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(wq,"vt %f %f" ,&t[bbp],&t[bbp+1]);


fseek(ww,pvc,SEEK_SET);
for(int c=0;c<cbw;c++)
fscanf(ww,"%[^\n]%*c",wq);
sscanf(&(*wq),"vn %f %f %f",  &ttk[bbh],  &ttk[bbh+1],  &ttk[bbh+2]);
wq;
bbh+=3;
bbp+=2;
}
while (1);
bba=(bbh)/3;

   
b=glm::lookAt(glm::vec3(-1.2484,0.483,1.84384), glm::vec3(-0.3801, -0.4183,-3.15),glm::vec3( 0., 0.2,-00.));
yt=glm::perspective(45., 1., 1.2, 300.);
bct=b*glm::mat4(1.);

b=yt*b*glm::mat4(1.);

bc=glm::transpose(glm::inverse(bct));

//b=glm::lookAt(glm::vec3(0., 0.,-1.),glm::vec3( 0., 0., 0.),glm::vec3( 0.,025.,-1.));
//yt=yt*b;

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

// glUniformMatrix4fv(1, 1, 0, glm::value_ptr(b));

  glGenVertexArrays(1, &gl_vao);

  glBindVertexArray(gl_vao);

	glGenBuffers(1, &gl_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, gl_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*bbh, verts, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


  glGenBuffers(1, &tpr);
  glBindBuffer(GL_ARRAY_BUFFER,tpr );

glBufferData(GL_ARRAY_BUFFER, sizeof(float)*bbp, t, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

 glGenBuffers(1, &tpra);
  glBindBuffer(GL_ARRAY_BUFFER, tpra);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*bbh, ttk  , GL_STATIC_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

glBindVertexArray(0);

glGenTextures(1, &vertexT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, vertexT);  

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA,  GL_UNSIGNED_BYTE,trr);

  return TRUE;
}

static gboolean render(GtkGLArea *area, GdkGLContext *context)
{
 
  glUseProgram(gl_program);

 glUniformMatrix4fv(10, 1, 0, &b[0][0]);
 glUniformMatrix4fv(13, 1, 0, &bct[0][0]);
 glUniformMatrix4fv(14, 1, 0, &bc[0][0]);

glUniform1i(11, 0);

  glBindVertexArray(gl_vao);


  glDrawArrays(GL_TRIANGLES,0,bba );

  glBindVertexArray (0);
  glUseProgram (0);


  glFlush();

  return TRUE;
}

int main(int argc, char** argv)
{


  gtk_init(&argc, &argv);

  GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL),
            *gl_area = gtk_gl_area_new();

  g_signal_connect(window,  "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(gl_area, "realize",      G_CALLBACK(realise),       NULL);
  g_signal_connect(gl_area, "render",       G_CALLBACK(render),        NULL);

  gtk_container_add(GTK_CONTAINER(window), gl_area);



  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}




