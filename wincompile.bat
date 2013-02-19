@echo off
cl lab1.cpp GlGlut.cpp Polyline.cpp Point.cpp /I "win32\include" /link "win32\lib\freeglut.lib"
echo ##################################################################
echo #Make sure execute permission is set on lab1.exe and freeglut.dll#
echo ##################################################################