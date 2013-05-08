/* GTK Mplayer test project in eclipse
 * by Stefan Weckend
 * Mplayer file header */

#ifndef _gtkwindow
#define _gtkwindow

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Mplayer {
private:
	FILE *mp_pipe;
	std::string binary_path;
	std::string parameter;
	std::string filepath;
public:
	void initialize(std::string bin, long xid);
	void exit();
	bool start_playback(std::string file);
	bool stop_playback();
	bool resume_playback();
	bool pause_playback();
	bool goto_time(int t);
};

#endif
