/* GTK Mplayer test project in eclipse
 * by Stefan Weckend
 * Main file */

#include <iostream>
#include <gtkmm.h>
#include <gdk/gdkx.h>
#include "mplayer.h"

using namespace std;

Glib::RefPtr<Gtk::Application> app;

struct mywidgets {
    //Main Window
    Gtk::Window *window_main;
    Gtk::DrawingArea *videoarea;
    Gtk::ImageMenuItem *item_open;
    Gtk::ImageMenuItem *item_open_url;
    Gtk::ImageMenuItem *item_close;
    Gtk::ImageMenuItem *item_about;
    Gtk::Button *btn_play;
    Gtk::Button *btn_stop;

    //About Window
    Gtk::Window *window_about;
    Gtk::Button *btn_about_ok;

    //URL open Window
    Gtk::Window *window_open_url;
    Gtk::Entry *entry_open_url;
    Gtk::Button *btn_open_url;
};

mywidgets widgets;
Mplayer mplayer;

void _item_close() {
    mplayer.exit();
    app->quit();
}

void _item_open() {
    Gtk::FileChooserDialog dialog_open("Datei öffnen", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog_open.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog_open.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    int result = dialog_open.run();
    switch(result) {
        case(Gtk::RESPONSE_OK): {
            string filename = dialog_open.get_filename();
            cout << filename << "\n";
            mplayer.start_playback(filename);
            break;
        }
        case(Gtk::RESPONSE_CANCEL):
            break;
        default:
            break;
    }
}

void _item_open_url() {
    widgets.window_open_url->show();
}

void _item_about() {
    widgets.window_about->show();
}

void _btn_about_ok() {
    widgets.window_about->hide();
}

void _btn_play() {
    mplayer.start_playback("/home/w33ky/Downloads/240P_400K_10729251.mp4");
}

void _btn_stop() {
    mplayer.stop_playback();
}

void _btn_open_url() {
    string path = widgets.entry_open_url->get_text();
    mplayer.start_playback(path);
    widgets.window_open_url->hide();
}

void run_gui(int argc, char** argv) {
    app = Gtk::Application::create(argc, argv, "de.gtkmm.mplayer");
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("gui.glade");

    builder->get_widget("window_main", widgets.window_main);
    builder->get_widget("videoarea", widgets.videoarea);
    builder->get_widget("item_open", widgets.item_open);
    builder->get_widget("item_open_url", widgets.item_open_url);
    builder->get_widget("item_close", widgets.item_close);
    builder->get_widget("item_about", widgets.item_about);
    builder->get_widget("btn_play", widgets.btn_play);
    builder->get_widget("btn_stop", widgets.btn_stop);

    widgets.item_open->signal_activate().connect(sigc::ptr_fun(&_item_open));
    widgets.item_open_url->signal_activate().connect(sigc::ptr_fun(&_item_open_url));
    widgets.item_close->signal_activate().connect(sigc::ptr_fun(&_item_close));
    widgets.item_about->signal_activate().connect(sigc::ptr_fun(&_item_about));
    widgets.btn_play->signal_clicked().connect(sigc::ptr_fun(&_btn_play));
    widgets.btn_stop->signal_clicked().connect(sigc::ptr_fun(&_btn_stop));

    builder->get_widget("window_about", widgets.window_about);
    builder->get_widget("btn_about_ok", widgets.btn_about_ok);

    widgets.btn_about_ok->signal_clicked().connect(sigc::ptr_fun(&_btn_about_ok));

    builder->get_widget("window_open_url", widgets.window_open_url);
    builder->get_widget("entry_open_url", widgets.entry_open_url);
    builder->get_widget("btn_open_url", widgets.btn_open_url);

    widgets.btn_open_url->signal_clicked().connect(sigc::ptr_fun(&_btn_open_url));

    widgets.window_main->show();

    GdkWindow *vid = gtk_widget_get_window(&widgets.videoarea->gobj()->widget);
    long xid = gdk_x11_window_get_xid(vid);
    mplayer.initialize("/usr/bin/mplayer", xid);

    app->run(*widgets.window_main);

    //delete(widgets.window_main);
}

int main(int argc, char** argv) {
    run_gui(argc, argv);
    return 0;
}
