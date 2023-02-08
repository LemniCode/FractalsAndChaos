#ifndef TEXT_H
#define TEXT_H

using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <string>

class text
{
    int pos_x, pos_y;
    string content;
    Color col;
    AlphaColor bg_col;
    bool displayed;
    int fontsize;

    int text_id;


public:
    text(int pos_x, int pos_y, string content);

    void display();

    void set_content(string n_content);
    void set_color(Color col);
    void set_background(AlphaColor col);
    void set_fontsize(int fontsize);
    void set_displayed(bool displayed);

    // Getters / setters
    void set_id(int text_id) { text::text_id = text_id; }
    int get_id() { return text_id; }

};

#endif // TEXT_H
