### tools of trade:  
  glsl  
  epoxy opengl pointers  
  libtarga  
  gtk+3  
### sys req 
opengl 3.3
## build 
```
c++ t.c libtarga.c  -std=c++11  `pkg-config --libs --cflags  gtk+-3.0 epoxy `  -o op
```
 