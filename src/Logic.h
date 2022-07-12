#pragma once
class Logic
{

public:
    void Load_Saved_Settings_Fans();

    void check_and_save_data_Fans();
    void check_and_save_data_display_settings();
    void load_saved_display_settings();
    void working_stream();
    void alarms();
    void alarms_page();
    void commands_from_display();
    void turn_unit_on();

    //void clogged_filters_alarm();
};
extern Logic logic_control;
