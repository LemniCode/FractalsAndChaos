#include "button.h"


button::button(int pos_x, int pos_y, int width, int height, string action, string text)
{
    button::pos_x = pos_x;
    button::pos_y = pos_y;
    button::width = width;
    button::height = height;
    button::action = action;
    button::text = text;

    // Default style
    // Colors
    button::col = Color(41); // light gray
    button::hover_col = Color(191); // dark gray
    button::text_col = Color(255); // Black
    button::hover_text_col = Color(0.); // White
    button::border_width = 2; // 2px
    button::border_col = Color(0.); // Black
    button::hover_border_col = Color(41); // dark gray
    // disabled
    button::disabled_col = Color(220); // lighter gray
    button::disabled_text_col = Color(170); // black
    button::disabled_border_col = Color(220); // gray
    // others
    button::fontsize = 9;


    button::hovered = false; // Default
    button::enabled = true; // Default
    button::displayed = true; // Default

}


void button::display() {

    if (!displayed) { return; }

    // Box
    Color bcol, tcol, bdcol; // button color, text color, border color
    if (!enabled) {
        bcol = disabled_col;
        tcol = disabled_text_col;
        bdcol = disabled_border_col;
    }
    else if (!hovered) {
        bcol = col;
        tcol = text_col;
        bdcol = border_col;
    }
    else {
        bcol = hover_col;
        tcol = hover_text_col;
        bdcol = hover_border_col;
    }

    fillRect(pos_x, pos_y, width, height, bcol);
    if (border_width > 0)
        drawRect(pos_x, pos_y, width, height, bdcol, border_width);

    // Text
    int margin = (height-fontsize*1.5)/2;
    drawString(pos_x+5, pos_y+height-margin, text, tcol, fontsize);

}

bool button::hovering(int mouse_x, int mouse_y) {
    return (mouse_x > pos_x && mouse_x < pos_x+width &&
            mouse_y > pos_y && mouse_y < pos_y+height);
}


// Changing button attributes
void button::set_text(string text) {
    button::text = text;
    display();
}

void button::set_enabled(bool enabled) {
    button::enabled = enabled;
    display();
}

void button::set_displayed(bool displayed) {
    button::displayed = displayed;
    display();
}

void button::set_fontsize(int fontsize) {
    button::fontsize = fontsize;
    display();
}

void button::set_border_width(int border_width) {
    button::border_width = border_width;
    display();
}

void button::set_color(string attr, Color col) {
    if (attr == "color")
        button::col = col;
    else if (attr == "hover_color")
        hover_col = col;
    else if (attr == "border_color")
        border_col = col;
    else if (attr == "text_color")
        text_col = col;
    else if (attr == "hover_text_color")
        hover_text_col = col;
    else if (attr == "hover_border_color")
        hover_border_col = col;
    else {
        cout << "There is no " << attr << " of type Color on button" << endl;
        return;
    }

    display();
}

void button::set_colors(string * attrs, Color * cols, int n_attrs) {
    for (int i=0; i < n_attrs; i++) {
        set_color(attrs[i], cols[i]);
    }
    display();
}






