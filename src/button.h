#ifndef BUTTON_H
#define BUTTON_H

using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <string>

// Button class
class button
{
    int pos_x, pos_y; // Top left coordinates
    int width, height; // width, height
    string action; // action upon click
    int button_id; // unique id

    // Style
    Color col;
    string text;

    // Additional
    Color hover_col;
    Color text_col;
    Color border_col;
    Color hover_text_col;
    Color hover_border_col;
    int border_width;
    int fontsize;

    // enabled
    Color disabled_col;
    Color disabled_border_col;
    Color disabled_text_col;


    // Auxiliar
    bool hovered;
    bool enabled;
    bool displayed;

public:
    button(int pos_x, int pos_y, int width, int height, string action, string text);

    // Returns true if mouse over button
    bool hovering(int mouse_x, int mouse_y);

    // displays button
    void display();

    // sets an attribute of the button
    void set_text(string text);
    void set_enabled(bool enabled);
    void set_displayed(bool displayed);

    void set_color(string attr, Color col);
    void set_colors(string attrs[], Color cols[], int n_attrs);

    void set_fontsize(int fontsize);
    void set_border_width(int border_width);


    // GETTERS / SETTERES
    void set_hovered(bool hovered) { button::hovered = hovered; }
    bool get_hovered() { return hovered; }
    string get_action() { return action; }
    bool get_enabled() { return enabled; }
    void set_id(int button_id) { button::button_id = button_id; }
    int get_id() { return button_id; }
    bool get_displayed() { return displayed; }

};

#endif // BUTTON_H
