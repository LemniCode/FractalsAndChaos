#include "text.h"

text::text(int pos_x, int pos_y, string content) {

    text::pos_x = pos_x;
    text::pos_y = pos_y;
    text::content = content;

    text::col = Color(51); // gray
    text::bg_col = AlphaColor(0, 0, 0, 0); // transparent
    text::displayed = true;
    text::fontsize = 10;

}

void text::display() {
    // background
    fillRect(pos_x-5, pos_y-5-fontsize*0.5, fontsize*0.85*content.length(), fontsize*1.5+10, bg_col);

    // text
    drawString(pos_x, pos_y+fontsize, content, col, fontsize);
}

void text::set_content(string n_content) {
    content = n_content;
    display();
}

void text::set_color(Color col) {
    text::col = col;
    display();
}

void text::set_background(AlphaColor col) {
    bg_col = col;
    display();
}

void text::set_fontsize(int fontsize) {
    text::fontsize = fontsize;
    display();
}

void text::set_displayed(bool displayed) {
    text::displayed = displayed;
    display();
}
