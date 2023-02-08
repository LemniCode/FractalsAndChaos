#include <Imagine/Graphics.h>
using namespace Imagine;
#include <cstdlib>
using namespace std;
#include <ctime>
#include "ui.h"
#include "simulator.h"
#include "constants.h"



;;;
simulator sim;

void display_simulator(simulator sim);

void init_ui(ui &ui);

bool perform_action(string action);
void perform_tool(string tool, int x, int y);

bool quit;
string tool = "none";

int res;

button * convergence_button;
bool convergence;
void set_convergence_style(bool on_off);
button * zoom_in_button;
text * tool_text;

int file_count = 0;
void save_png_file(string file_name);

int main() {

    openWindow(WIDTH, HEIGHT);

    noRefreshBegin();

    // Initialisation
    tool = "trajectory";
    res = 5;
    convergence = true;

    // User interface
    ui ui(UI_END, HEIGHT);
    init_ui(ui);

    // Redraw everything
    fillRect(0, 0, WIDTH, HEIGHT, BG_COL);
    ui.refresh();
    noRefreshEnd();

    const int n_planets = 5;
    Vector2 planets_pos[5] = {createVector(-.4, -.3), createVector(0.6, 0.5), createVector(0.2, 0.8), createVector(-.4, .6), createVector(.8, -.7)};
    double planets_mass[5] = {0.5, 1., 2., 1., 2.};
    double planets_rad[5] = {0.07, 0.07, 0.07, 0.07, 0.07};
    Color planets_color[5] = {RED, BLUE, YELLOW, PURPLE, GREEN};
    // FOUR PLANETS
    //Vector2 planets_pos[4] = {createVector(-.4, -.3), createVector(0.6, 0.5), createVector(0.2, 0.8), createVector(-.4, .6)};
    //double planets_mass[4] = {0.5, 1., 2., 1.};
    //double planets_rad[4] = {0.07, 0.07, 0.07, 0.07};
    //Color planets_color[4] = {Color(127, 88, 175), Color(100, 197, 235), Color(232, 77, 138), Color(254, 179, 38)};
    // THREE PLANETS
    //Vector2 planets_pos[3] = {createVector(-.4, -.3), createVector(0.6, 0.5), createVector(0.2, 0.8)};
    //double planets_mass[3] = {0.5, 1., 2.};
    //double planets_rad[3] = {0.07, 0.07, 0.07};
    //Color planets_color[3] = {RED, BLUE, GREEN};
    // TWO PLANETS
    //Vector2 planets_pos[n_planets] = {createVector(-.4, -.3), createVector(0.6, 0.5)};
    //double planets_mass[n_planets] = {1., 1.};
    //double planets_rad[n_planets] = {0.07, 0.07};
    //Color planets_color[n_planets] = {RED, BLUE};

    sim = simulator(createVector(0., 0.), 1, 0.01, 1, 5000, planets_pos,
                              planets_mass, planets_rad, planets_color, n_planets, WIDTH-UI_END,
                               HEIGHT, UI_END, 0, convergence);


    display_simulator(sim);

    cout << "The saved images can be located at " << srcPath("images") << endl;


    Event ev;
    quit = false;
    while (!quit) {
        getEvent(1000/REFRESH_RATE, ev); // Wait until event occurs

        string action = ui.handle_event(ev);
        if (action == "outside_ui")
            perform_tool(tool, ui.last_click_x, ui.last_click_y);
        else
            quit = perform_action(action);
    }


    return 0;
}


// Displays the simulator. Run on separate thread
void display_simulator(simulator sim) {
    sim.display(res);
}


void perform_tool(string tool, int x, int y) {

    if (tool == "trajectory") {
        for (int i=0; i<20; i++) {
            double param;
            if (sim.get_zoom() > 1)
                param = sim.get_zoom();
            else
                param = 1;
            sim.show_trajectory(x+(float)(rand()%1000)/1000.-0.5-UI_END, y+(float)(rand()%1000)/1000.-0.5, param);
        }
    }

}

// Performs action asociated with string
// Returns true if action is quit
bool perform_action(string action) {

    if (action == "quit") {
        return true;
    }
    else if (action == "cout") {
        cout << "Say something!" << endl;
    }
    else if (action.substr(0, 4) == "move") {
        int dir[2] = {0, 0};
        if (action == "move_up") dir[1] = -1;
        else if (action == "move_down") dir[1] = 1;
        else if (action == "move_left") dir[0] = -1;
        else dir[0] = 1;
        sim.move_center(dir);
        display_simulator(sim);
    }
    else if (action.substr(0, 4) == "zoom") {
        if (action == "zoom_in") {
            if (sim.zoom_in() <= 7.10543e-15) {

                // MAX ZOOM REACHED
                zoom_in_button->set_enabled(false);
                zoom_in_button->display();
            }
        }
        else {
            sim.zoom_out();
            zoom_in_button->set_enabled(true);
            zoom_in_button->display();
        }
        display_simulator(sim);
    }
    else if (action.substr(0, 7) == "quality") {
        if (action.length() == 9)
            res = 10;
        else
            res = action[7]-'0';
        display_simulator(sim);
    }
    else if (action == "toggle_convergence") {
        convergence = !convergence;
        set_convergence_style(convergence);
        sim.set_convergence(convergence);
        display_simulator(sim);
    }
    else if (action == "trajectories_tool") {
        tool = "trajectory";
        tool_text->set_content("Current tool: trajectories");
    }
    else if (action == "save_frame") {
        time_t millis = time(nullptr);
        save_png_file(srcPath("images/save" + to_string(file_count++) + "_" + to_string((int)millis) + ".jpg"));
    }
    else if (action == "film_zoom_out") {
        res = 1;
        time_t millis = time(nullptr);
        int count = 0;
        while(sim.get_zoom() <= 2) {
            display_simulator(sim);
            save_png_file(srcPath("images/save_" + to_string((int)millis) + "_zoom_"+to_string(count++) + ".jpg"));
            sim.zoom_out(2.5);
        }


    }
    else if (action == "none") {
        // do nothing
    }

    return false;
}


// Initializes the UI. Main purpose is to keep main clean
void init_ui(ui &ui) {
    text * t;
    button * b;
    // Title
    t = ui.create_text(30, 30, "CHAOS FRACTALS");
    t->set_color(WHITE);
    t->set_fontsize(15);
    ui.create_button(20, HEIGHT-50, 70, 30, "quit", "QUIT");
    // MOVE tool
    t = ui.create_text(20, 80, "MOVE");
    t->set_color(Color(200));
    ui.create_button(90, 70, 30, 30, "move_up", "U");
    ui.create_button(130, 70, 30, 30, "move_down", "D");
    ui.create_button(170, 70, 30, 30, "move_left", "L");
    ui.create_button(210, 70, 30, 30, "move_right", "R");
    // ZOOM tool
    t = ui.create_text(20, 130, "ZOOM");
    t->set_color(Color(200));
    zoom_in_button = ui.create_button(90, 120, 30, 30, "zoom_in", "+");
    ui.create_button(130, 120, 30, 30, "zoom_out", "-");
    // Convergence time toggle
    t = ui.create_text(20, 180, "Show convergence");
    t->set_color(Color(200));
    convergence_button = ui.create_button(200, 160, 50, 40, "toggle_convergence", "ON");
    convergence_button->set_border_width(3);
    convergence_button->set_color("color", Color(100)); // Gray
    set_convergence_style(convergence);

    t = ui.create_text(20, 220, "Quality");
    t->set_color(Color(200));
    ui.create_button(90, 210, 30, 30, "quality10", "10");
    ui.create_button(130, 210, 30, 30, "quality5", "5");
    ui.create_button(170, 210, 30, 30, "quality3", "3");
    ui.create_button(210, 210, 30, 30, "quality2", "2");
    ui.create_button(250, 210, 30, 30, "quality1", "1");

    t = ui.create_text(20, 284, "Tool");
    t->set_color(Color(200));
    b = ui.create_button(80, 270, 100, 30, "trajectories_tool", "trajectories");
    tool_text = ui.create_text(20, 330, "Current tool: trajectories");
    tool_text->set_color(Color(255));
    ui.create_button(20, 370, 100, 40, "save_frame", "Save image");
    ui.create_button(150, 370, 130, 40, "film_zoom_out", "Zoom out film");
}


void set_convergence_style(bool on_off) {
    if (!on_off) {
        convergence_button->set_color("border_color", Color(255, 0, 0)); // Red
        convergence_button->set_color("hover_border_color", Color(0, 255, 0)); // Green
        convergence_button->set_text("OFF");
    }
    else {
        convergence_button->set_color("border_color", Color(0, 255, 0)); // Green
        convergence_button->set_color("hover_border_color", Color(255, 0, 0)); // red
        convergence_button->set_text("ON");
    }
    convergence_button->display();
}


void save_png_file(string file_name) {
    cout << "Saving image as " << file_name << endl;
    Color cols[(WIDTH-UI_END)*HEIGHT];
    captureRectangle(UI_END, 0, cols, WIDTH-UI_END, HEIGHT);
    saveColorImage(file_name, cols, WIDTH-UI_END, HEIGHT);
}

