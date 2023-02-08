#include "simulator.h"



simulator::simulator(Vector2 center, double zoom, double dt, double G, int max_iters,
                     Vector2 planets_pos[], double planets_mass[], double planets_rad[], Color planets_color[],
                     int n_planets, int width, int height, int topl_x, int topl_y, bool show_convergence) {
    simulator::center = center;
    simulator::zoom = zoom;
    simulator::dt = dt;
    simulator::G = G;
    simulator::n_planets = n_planets;
    simulator::width = width;
    simulator::height = height;
    simulator::topl_x = topl_x;
    simulator::topl_y = topl_y;
    simulator::max_iters = max_iters;
    planets = new Planet[n_planets];
    for (int i=0; i<n_planets; i++) {
        planets[i].pos = planets_pos[i];
        planets[i].mass = planets_mass[i];
        planets[i].radius = planets_rad[i];
        planets[i].col = planets_color[i];
    }
    simulator::show_convergence = show_convergence;
}

Vector2 simulator::pix_2_world(int x, int y) {
    Vector2 res;
    res.x = 2.*x/width-1; // (0, width) -> (-1, 1)
    res.y = 2.*y/height-1; // (0, height) -> (-1, 1)
    //res.x = res.x*zoom + center.x; // (-1, 1) center.x-zoom, center.x+zoom
    //res.y = res.y*zoom + center.y; // (-1, 1) center.x-zoom, center.x+zoom
    res = res*zoom + center;
    return res;
}
void simulator::world_2_pix(Vector2 pos, int & x, int & y, double custom_zoom) {
    if (custom_zoom == -1)
        custom_zoom = zoom;
    pos = (pos-center)/custom_zoom; // center +- zoom -> (-1, 1)
    pos = (pos + 1)/2; // (-1, 1) -> (0, 1)
    x = int(pos.x*width);
    y = int(pos.y*height);
}


// Returns color of planet simulation
Color simulator::get_pixel_color(Vector2 pos, int & iters) {

    iters = 0;
    Vector2 vel = createVector(0., 0.);
    Vector2 acc;

    while (iters < max_iters) {
        int planet = converged(pos);
        if (planet != -1)
            return planets[planet].col;

        // Calculate acc at point
        acc = get_acc(pos);
        vel = vel + acc*dt;
        pos = pos + vel*dt;

        iters++;
    }

    return Color(255); // White if didnt converge
}



// Calculates the acceleration given a position
Vector2 simulator::get_acc(Vector2 pos) {

    Vector2 acc = createVector(0., 0.); // Start with 0s

    for (int i=0; i<n_planets; i++) {
        // Calculate acc for planet
        Planet p = planets[i];
        Vector2 dir = p.pos-pos;
        double dist = norm(dir);
        dir = dir / dist;
        acc = acc + dir * (G * p.mass / (dist*dist));
    }

    return acc;
}

void simulator::show_trajectory(Vector2 pos, double param) {
    int iters = 0;
    Vector2 vel = createVector(0., 0.);
    Vector2 acc;
    int x, y;
    int prev_x, prev_y;
    world_2_pix(pos, prev_x, prev_y, param);
    Color col = Color(255., 255., 255.);

    while (iters < max_iters) {
        int planet = converged(pos);
        if (planet != -1)
            return;

        // Calculate acc at point
        acc = get_acc(pos);
        vel = vel + acc*dt;
        pos = pos + vel*dt;

        world_2_pix(pos, x, y, param);

        drawLine(topl_x + prev_x, topl_y + prev_y, topl_x + x, topl_y + y, col);
        prev_x = x;
        prev_y = y;

        iters++;
    }
}


// Checks (and returns index of) if has converged to any planet
int simulator::converged(Vector2 pos) {

    for (int i=0; i<n_planets; i++) {
        if (norm(pos-planets[i].pos) < planets[i].radius)
            return i;
    }

    // If didnt converge return -1
    return -1;
}


// Displays all colors from top left corner
void simulator::display(int res) {

    int iters = 0;
    fillRect(topl_x+width/2-150, topl_y+height/2-20, 300, 40, AlphaColor(255., 255., 255., 180));
    drawString(topl_x+width/2-120, topl_y+height/2+6, "Computing trajectories", Color(0.));


    // Show pixels
    for (int i=0; i<width; i+=res) {
        for (int j=0; j<height; j+=res) {
            Color col = get_pixel_color(i, j, iters);
            if (show_convergence) {
                // Interpolate between col and white linearly trough iters
                col = Color(col.r() + (255-col.r())*iters/max_iters,
                                col.g() + (255-col.g())*iters/max_iters,
                                col.b() + (255-col.b())*iters/max_iters);
            }
            // Instead of drawing to the screen, draw to image and then show
            fillRect(topl_x+i, topl_y+j, res, res, col);
        }
    }

    // Show planets
    int x, y;
    for (int i=0; i<n_planets; i++) {
        world_2_pix(planets[i].pos, x, y);
        fillCircle(topl_x + x, topl_y + y, 10/zoom, BLACK);
    }
}

// TOOLS
// Moves the center of the simulation zoom/3
void simulator::move_center(int dir[2]) {
    center = center + createVector(dir[0], dir[1])*zoom/3;
}
double simulator::zoom_in() {
    zoom *= 0.5;
    return zoom;
}
double simulator::zoom_out(double times) {
    zoom *= 2*times;
    return zoom;
}




