# 3DViever_v2
3DViever to show .obj files in wireframe view

## Short app description

The application is to draw 3d models in wireframe view (just points and lines). The only one model can be loaded at the one time. As well, it is possible to rotate, move, scale model by 3 axes (X, Y and Z), setup points ad lines colors, sizes and type (round/square for points and solid/stipple for lines), take a screenshot and GIF animation recording for 5 seconds.

The application developed in C language of C11 standard using GCC compiler. As a GUI creation technology chosen QT6 library with C++ underneath. The application source code located in the src folder and can be built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests, gcov_report.

## Interface

### The application interface includes:

1. View port: The main field of window where 3d model is to draw. Open new model can be executed by short-key (command + O) or from menubar (File -> Open new file).

2. Steer panel: To open it is possible by short-key (commad + P) or from the menubar (View -> Steer panel). Steer panel may contains 3 widgets to manage model drawn. To manage these widgets it is possible by menubar. View -> Transform (command + 1) - to manage widget to steer model position in view port. View -> View setup (command + 2) - to manage widget to steer model style. View -> Screen (command + 3) capture - to manage widget to take screenshot or record a GIF. Steer panel implemented as dock-widget, so there is possibility to undock it from main window and move around display.

### Steering model by mouse: 

Model can be rotated by mouse just with pressed left mouse button, scaled by just mouse wheel. Also, model can be moved by mouse with pressed left mouse button and space key simultaneously by X and Y axis and by left mouse button, space key simultaneously and wheel by Z axis.
@end enumerate

## Instruction

To install the application the "make install" command execution is required in "src" folder. The application to launch will be located in "build" folder of the project root.

Uninstallation is done through execution "make uninstall" command. Thus, the executable file will be deleted from "build" folder.