#ifndef UI_H
#define UI_H

#include <list>

#include "button.h"
#include "text.h"



class ui
{
    button** buttons; // Array of buttons
    text** texts;
    int text_id;
    int button_id;

    int width, height;
    // Highlights on hover buttons.
    // Actions on clicks
    // Change buttons state
    void update(int mouse_x, int mouse_y);

    // Returns pointer to current button or null (if none)
    string get_clicked_action();

public:
    ui(int width, int height);

    int last_click_x, last_click_y;

    // Create a new button
    // Returns id of button. To handle actions over buttons
    button * create_button(int pos_x, int pos_y, int width, int height, string action, string text);

    // Returns the button
    button * get_button(int button_id);

    text * create_text(int pos_x, int pos_y, string content);
    text * get_text(int text_id);

    void refresh();

    // Handles user events
    // Returns string with action to perform
    string handle_event(Event ev);
};

#endif // UI_H
