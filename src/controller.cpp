#include "controller.h"
#include "my_webserver.h"
#include "weather_app.h"
#include "clock_app.h"

state_t states[2];
bool is_weather_text;

void set_state(state_t state, row_t row){
    states[row] = state;
    if (state != MESSAGE){
        if (state == WEATHER) weather_init();
        if (states[0] == states[1]){
            row_t r = (row_t)((row + 1)%2);
            set_state(MESSAGE, r);
            screen_print("", r);
        }
    }
}

void set_state(state_t state, row_t row, bool b){
    states[row] = state;
    if (state != MESSAGE){
        if (state == WEATHER) {
            weather_init();
            is_weather_text = b;
        }
        if (states[0] == states[1]){
            row_t r = (row_t)((row + 1)%2);
            set_state(MESSAGE, r);
            screen_print("", r);
        }
    }
}

void controller_init(){
    clock_init(7200, 0, "pl.pool.ntp.org", "%m-%d   %H:%M:%S");
    webserver_init();
	weather_init();
}

void controller_update(){
    screen_update();
    for (int i = 0; i < 2; i++){
        switch (states[i]) {
            case WEATHER:
                weather_update((row_t)i, is_weather_text);
                break;
            
            case CLOCK:
                clock_update((row_t)i);
                break;

            default:
                break;
        }
    }
    webserver_update();
}