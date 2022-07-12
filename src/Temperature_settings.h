#pragma once
class Temperature_settings
{
private:
    /* data */
public:
    void working_stream();
    void refresh_screen();
    bool summer_winter_mode();
    void save_settings();
    void load_settings();
    void commands_from_display();
};

extern Temperature_settings temperature_settings_control;