#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "math2d.h"
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;



struct Planet {
    Vector2 pos;
    double mass;
    double radius;
    Color col;
};


class simulator {
    Vector2 center;
    double zoom;
    Planet * planets;
    int n_planets;
    int width, height, topl_x, topl_y;

    int max_iters;

    double dt;

    double G;

    bool show_convergence;

    Color * colors;

    // Calculates the acceleration for a given position
    Vector2 get_acc(Vector2 pos);

    // Chekcs if has converged to any planet
    int converged(Vector2 pos);

public:
    simulator() {};
    simulator(Vector2 center, double zoom, double dt, double G, int max_iters,
              Vector2 planets_pos[], double planets_mass[], double planets_rad[],  Color planets_color[],
              int n_planets, int width, int height, int topl_x, int topl_y, bool show_convergence);

    // Convert pixel coordinates to world coordinates
    Vector2 pix_2_world(int x, int y);

    // Computes in x, y the pixel corresponding to pos
    void world_2_pix(Vector2 pos, int & x, int & y, double custom_zoom = -1);


    // Returns color of planet simulation
    Color get_pixel_color(Vector2 pos, int & iters);

    // Returns color of planet simulation
    Color get_pixel_color(int x, int y, int & iters) {
        return get_pixel_color(pix_2_world(x, y), iters);
    }


    // Displays all colors from top left corner
    void display(int res);

    // Shows a trajectory
    void show_trajectory(Vector2 pos, double param);

    void show_trajectory(double x, double y, double param) {
        show_trajectory(pix_2_world(x, y), param);
    }

    // TOOLS
    // Moves the center of the simulation zoom/3
    void move_center(int dir[2]);
    // zooms in
    double zoom_in();
    double zoom_out(double times = 1.);
    void set_convergence(bool conv) {
        show_convergence = conv;
    }
    double get_zoom() { return zoom; }
};


#endif // SIMULATOR_H
