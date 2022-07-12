#pragma once

class Heaters_settings
{
private:
    /* data */
public:
    void working_stream();
    void heater1_enabled();
    void heater2_enabled();
    void heater3_enabled();
    void commands_from_display();
    void refresh_page();
    void h1_settings();
    void h2_settings();
    void h3_settings();
    void refresh_page_h1_settings();
    void refresh_page_h2_settings();
    void refresh_page_h3_settings();
    void save_settings_heater1();
    void save_settings_heater2();
    void save_settings_heater3();
    void load_saved_settings_heater1();
    void load_saved_settings_heater2();
    void load_saved_settings_heater3();
    void save_heaters_settings_p14();
    void load_heaters_settings_p14();
};

extern Heaters_settings heaters_settings_control;
