#include "ui.h"


ui::ui(int width, int height)
{
    enableMouseTracking(true);
    button_id = 0;
    text_id = 0;
    buttons = new button*[20]; // init size
    texts = new text*[20];
    ui::width = width;
    ui::height = height;
    last_click_x = 0;
    last_click_y = 0;
}

button * ui::create_button(int pos_x, int pos_y, int width, int height, string action, string text) {
    buttons[button_id] = new button(pos_x, pos_y, width, height, action, text);
    button * b = buttons[button_id];
    b->display();
    b->set_id(button_id++);
    return buttons[b->get_id()];
}

text * ui::create_text(int pos_x, int pos_y, string content) {
    texts[text_id] = new text(pos_x, pos_y, content);
    text * t = texts[text_id];
    t->display();
    t->set_id(text_id++);
    return texts[t->get_id()];
}


void ui::update(int mouse_x, int mouse_y) {
    for (int i=0; i<button_id; i++) {
        button * b = buttons[i];
        // If button is being hovered:
        if (b->get_hovered()) {
            // If it is not hovered anymore change state
            if (!b->hovering(mouse_x, mouse_y)) {
                b->set_hovered(false);
                b->display();
            }
        }
        else { // Button not being hovered
            // If is getting hovered
            if (b->hovering(mouse_x, mouse_y)) {
                b->set_hovered(true);
                b->display();
            }
        }
    }

}




string ui::handle_event(Event ev) {

    switch (ev.type) {

        case EVT_MOTION: { // Mouse move
            update(ev.pix.x(), ev.pix.y());
            break;
        }
        case EVT_BUT_ON: { // Mouse click
            // get button clicked and return its action
            last_click_x = ev.pix.x();
            last_click_y = ev.pix.y();
            if (last_click_x > width || last_click_y > height)
                return "outside_ui";
            return get_clicked_action();
        }
            break;

        case EVT_KEY_ON: // Key pressed

            break;

        default:
        case EVT_NONE:
            // Nothing
            break;
    }

    return "none";
}


void ui::refresh() {
    for (int i=0; i<button_id; i++) {
        buttons[i]->display();
    }
    for (int i=0; i<text_id; i++) {
        texts[i]->display();
    }
}


button* ui::get_button(int current_id) {
    for (int i=0; i<button_id; i++) {
        button * b = buttons[i];
        if (b->get_id() == current_id)
            return b;
    }
    cout << "ID " << current_id << " of buttons not used" << endl;
    return NULL;
}

text* ui::get_text(int current_id) {
    for (int i=0; i<text_id; i++) {
        text * t = texts[i];
        if (t->get_id() == current_id)
            return t;
    }
    cout << "ID " << current_id << " of texts not used" << endl;
    return NULL;
}





// Gets action of currently hovered button
string ui::get_clicked_action() {
    for (int i=0; i<button_id; i++) {
        button * b = buttons[i];
        if (b->get_enabled() && b->get_hovered())
            return b->get_action();
    }
    return "none";
}
