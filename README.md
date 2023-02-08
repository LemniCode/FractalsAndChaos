# Fractals And Chaos

In this repo you can find the code for the UI tool used to develop the Chaos and Fractal project, as well as the written report in PDF format. Note that the tool is written in c++ using the Imagine++ library for graphics.

## Short Introduction

In this project the world of fractals will be explored. In particular, we will use the inherit chaos in a simple dynamical system to generate very interesting fractals. Imagine a 2D world where there are 2 planets: planet BLUE and planet RED. Now imagine we, as 3D beings, wanted to paint this 2D world. So, we choose a point in the plane, launch a spaceship from that point, and we watch what planet said point converges to. The spaceship lands on planet RED, so we paint that point RED. Then we repeat this process for every point in the plane and we get this image:

![image](https://user-images.githubusercontent.com/122687797/217568171-59dd58e5-e9c6-44f4-bc74-80769a0f84c5.png)

For example, in the image you can see the trajectory of one of the spaceships, which ends up converging to the red planet, hence that point is painted red. Since we are using a computer, with limited CPU and memory, we cannot run this simulation for every point in the plane. So, we divide the plane into squares, the smaller the squares the better the resolution of our image.

In this project we will first build a C++ application that allows us to explore this new world we created. Then, we will use it to observe the fractals that emerge in this world. Finally, we will draw conclusions on why chaos is connected with fractals.

![image](https://user-images.githubusercontent.com/122687797/217568188-11796893-db8e-4c47-9bdd-3ecbe01aaf31.png)
