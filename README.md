# OpenGL PCG - Dissertation Project

![Four examples of procedurally generated terrain](https://i.imgur.com/3YqxKAU.png)

This is a repository for the final project and dissertation I developed for my BSc in Computer Science. As it has been a while since this was graded, I thought it would be interesting to show the code and associated documentation publicly, as it is designed to be used and reused.

The abstract of the dissertation gives an overview of the project - 
> This project explores the concepts of coherent noise in order to develop a procedural content generator. Procedural generation and its applications are examined, and types of coherent noise are compared and contrasted.

> An OpenGL system is built from first principles and is then combined with the Perlin noise algorithm in order to generate pseudorandom 3D terrain. Control over parameters affecting the result is given to the user, such that a potentially infinite set of results can be produced. The result is a program that demonstrates the potential of coherent noise, alongside an engine that can be reused and easily built upon further. Consideration is given to how the procedural generator scores against modern criteria.

The codebase is essentially split into two key parts:
* The graphical engine, 'EngineLib', containing all the classes that interact with OpenGL in order to produce 3D graphics. Additionally contains the logic of the Perlin noise algorithm, and a class that produces procedurally generated terrain using the algorithm.
* The procedural generator application, using the engine library and a Qt user interface to allow control over the produced results.

Instructions for use can be found in `How to use.txt`. A full description of background theory, the development process (with images!) and a critical analysis of the project can be found in the dissertation pdf.

## External Libraries
The following external libraries are used in this project:
* [GLEW](http://glew.sourceforge.net)
* [GLFW](https://www.glfw.org)
* [GLM](https://glm.g-truc.net/0.9.9/index.html)
* [Qt](https://www.qt.io)
