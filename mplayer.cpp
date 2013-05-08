/* GTK Mplayer test project in eclipse
 * by Stefan Weckend
 * Mplayer file */

#include "mplayer.h"

void Mplayer::initialize(std::string bin, long xid) {
	binary_path = bin;
	std::string sxid;
	std::stringstream mystream;
	mystream << xid;
	sxid = mystream.str();
	parameter = " -wid ";
	parameter += sxid;
	parameter += " -slave -quiet -idle &> mplayer.log";
	std::string execute = binary_path;
	execute += parameter;
	mp_pipe = popen(execute.c_str(), "w");
}

void Mplayer::exit() {
	fputs("quit\n", mp_pipe);
	fflush(mp_pipe);
	pclose(mp_pipe);
}

bool Mplayer::start_playback(std::string file) {
	std::string todo = "loadfile \"";
	todo += file;
	todo += "\" \n";
	fputs(todo.c_str(), mp_pipe);
	fflush(mp_pipe);
	return true;
}

bool Mplayer::stop_playback() {
	fputs("stop\n", mp_pipe);
	fflush(mp_pipe);
	return true;
}

bool Mplayer::resume_playback() {
	return true;
}

bool Mplayer::pause_playback() {
	return true;
}

bool Mplayer::goto_time(int t) {
	return true;
}
