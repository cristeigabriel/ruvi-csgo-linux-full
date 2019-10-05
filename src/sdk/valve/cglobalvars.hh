///
///  ruvi base
///

class c_global_vars {
public:
	float real_time;
	int frame_count;
	float absolute_frametime;
	float absolute_frame_start_timestd_dev;
	float cur_time;
	float frame_time;
	int max_clients;
	int tick_count;
	float interval_per_tick;
	float interpolation_amount;
	int sim_ticks_this_frame;
	int network_protocol;
	void* p_save_data;
	bool client;
	int timestamp_networking_base;
	int timestamp_randomize_window;
};