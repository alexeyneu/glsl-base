## build :
```
c++ t.c --target=arm-linux-gnu -std=c++11  `pkg-config --libs --cflags  gtk+-3.0 epoxy `  -o op -lOpenImageIO -lopencv_videoio
```
 -  gtk3 opencv:
...clone opencv
```
cd opencv
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/ -D BUILD_opencv_videoio=ON -D WITH_IPP=OFF   -D WITH_GTK=ON -D WITH_GTK3=ON  -D WITH_FFMPEG=ON -D WITH_V4L=ON -D WITH_LIBV4L=ON WITH_HAL=ON WITH_OPENGL=ON WITH_VIDEOINPUT=ON   ../ 
```
...target is : `FFMPEG ON , DC1394(both)  OFF ` .
 I'd gain it by 
```
sudo apt install *highgui* 
sudo apt purge  libraw1394-* libraw1394-tools* libdc1394-22-???
```

- next
```
make
sudo make install
sudo ldconfig

sudo apt install libopenimageio*
locate libopencv_highgui.so.2.4
sudo rm (located dir)/libopencv_highgui.so.2.4

sudo link /usr/lib/libopencv_highgui.so.3.2.0 (located dir )/libopencv_highgui.so.2.4
```
