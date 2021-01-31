#pragma once
class Logic
{

public:
    void Load_Saved_Settings_Fans();

    void check_and_save_data_Fans();
    void check_and_save_data_display_settings();
    void load_saved_display_settings();
    bool turn_everything_off();
    void working_stream();

    void read_DS18B20_temperatures_core_0(void *parameter);
};
extern Logic logic_control;
