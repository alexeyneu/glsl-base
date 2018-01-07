![Screen1](screen/Screenshot%208.jpg)
### tools of trade:  
  epoxy opengl pointers  
  libtarga  
  gtk+3  
  art of illusion soft used also -  
  ( `Untitled.obj` ) spline mesh , handier then blender  
### sys req 
opengl 3.3
## build 
```
c++ t.c libtarga.c  -std=c++11  `pkg-config --libs --cflags  gtk+-3.0 epoxy `  -o op
```
### dependencies
parrot 3.9 had enouth after
```
sudo apt install libgtk-3-* libglm-*
``` 
if not : 
```
sudo apt install *epoxy*
```