#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;
class Name_text {
private:
	Font font;
public:
	Text text;
public:
	void set_text(int x, int y, string name) {
		if (name.length()>7) {
			name.erase(4, 20);
			name = name + "...";
		}
		font.loadFromFile("fonts/myfont.ttf");
		text.setString(name);
		text.setFillColor(Color::White);
		text.setCharacterSize(50);
		text.setFont(font);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setPosition(x, y);
	}
};
class Button {
private:
	string texture_name, texture_p_name;
public:
	float x_pos, y_pos, length, height;
	Sprite sprite, sprite_p;
	Texture texture, texture_p;
public:
	void set_length(int l) { length = l; }
	void set_height(int h) { height = h; }
	int get_length() { return length; }
	int get_height() { return height; }
	void set_texture_name(string name) { texture_name = name; }
	string get_texture_name() { return texture_name; }
	void set_texture_p_name(string name) { texture_p_name = name; }
	string get_texture_p_name() { return texture_p_name; }
	void set_texture(RenderWindow & window) { 
		if (IntRect(x_pos, y_pos, get_length(), get_height()).contains(Mouse::getPosition(window)))
		texture.loadFromFile(get_texture_p_name()); 
		else
		texture.loadFromFile(get_texture_name());
	}
	void set_sprite() { sprite.setTexture(texture); }
	void set_buttom_pos(int x, int y) {
		x_pos = x; y_pos = y;
		sprite.setPosition(x_pos,y_pos);
	}
	bool is_pressed(RenderWindow & window) {
		if (IntRect(x_pos, y_pos, get_length(), get_height()).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left)) { return true; }
		else return false;
	}
}; 
class AudioTrack {
private:
	string track_name;
	int track_number;
public:
	SoundBufferRecorder rec;
	SoundBuffer buffer;
	Sound sound;
public:
	void set_track_name() {
		string name;
		again : cout << "Введите название дорожки (не более 7-ми символов):" << endl; cin >> name; system("cls");
		ifstream file;
		file.open(name + ".ogg");
		if(file){
        cout << "Такой файл существует!!! Введите другое имя:" << endl;
		goto again;
		}
		else
		track_name = name;
	}
	void set_track_number(int number) { track_number = number; }
	string get_track_name() { return track_name+".ogg"; }
	string get_name_of_track() { return track_name; }
	int get_track_number() { return track_number; }
	void start_rec() {rec.start();}
	void stop_rec() { 
		rec.stop();
		buffer = rec.getBuffer();
		buffer.saveToFile(get_track_name());
	}
	void play_this_track() {
		buffer.loadFromFile(get_track_name());
		sound.setBuffer(buffer);
		sound.play();
	}
	void stop_play() { sound.stop(); };
};
void set_buttons_pos(bool is_checked[10], int &i, Button play[10], Button stop[10], Button del[10], Button check_t[10], Button check_f[10], Button &add_one, Button &play_all, Button &stop_rec) {
	if (i > 0) {
		for (int n = i - 1; n >= 0; n--) {
			play[n].set_buttom_pos(200, n * 80 + 5);
			stop[n].set_buttom_pos(280, n * 80 + 5);
			if (is_checked[n] == 1){
				check_t[n].set_buttom_pos(360, n * 80 + 5);
			check_f[n].set_buttom_pos(0, 0);
		}
			if (is_checked[n] == 0){
				check_f[n].set_buttom_pos(360, n * 80 + 5);
			check_t[n].set_buttom_pos(0, 0);
		}
			del[n].set_buttom_pos(440, n*80 + 5);
		}
	}
	add_one.set_buttom_pos(1148,5);
	play_all.set_buttom_pos(1148,223);
	stop_rec.set_buttom_pos(1148,441);
}
void set_button_sprite (RenderWindow & window, bool is_checked[10], int &i, Button play[10], Button stop[10], Button del[10], Button check_t[10], Button check_f[10], Button &add_one, Button &play_all, Button &stop_rec) {
	if (i > 0) {
		for (int n = i-1; n >= 0; n--) {
			play[n].set_texture_name("images/play.png");
			play[n].set_texture_p_name("images/play_p.png");
			play[n].set_texture(window);
			play[n].set_sprite();
			stop[n].set_texture_name("images/stop.png");
			stop[n].set_texture_p_name("images/stop_p.png");
			stop[n].set_texture(window);
			stop[n].set_sprite();
			if (is_checked[n] == 1) {
				check_t[n].set_texture_name("images/check_t.png");
				check_t[n].set_texture_p_name("images/check_t_p.png");
				check_t[n].set_texture(window);
				check_t[n].set_sprite();
			}
			if (is_checked[n] == 0) {
				check_f[n].set_texture_name("images/check_f.png");
				check_f[n].set_texture_p_name("images/check_f_p.png");
				check_f[n].set_texture(window);
				check_f[n].set_sprite();
			}
			del[n].set_texture_name("images/del.png");
			del[n].set_texture_p_name("images/del_p.png");
			del[n].set_texture(window);
			del[n].set_sprite();
		}
	}
	add_one.set_texture_name("images/add_one.png");
	add_one.set_texture_p_name("images/add_one_p.png");
	add_one.set_texture(window);
	add_one.set_sprite();
	play_all.set_texture_name("images/play_all.png");
	play_all.set_texture_p_name("images/play_all_p.png");
	play_all.set_texture(window);
	play_all.set_sprite();
	stop_rec.set_texture_name("images/stop_rec.png");
	stop_rec.set_texture_p_name("images/stop_rec_p.png");
	stop_rec.set_texture(window);
	stop_rec.set_sprite();
}
void set_text(Name_text name[10], AudioTrack track[10], RenderWindow & window, int &i) {
	if (i > 0) {
		for (int n = i - 1; n >= 0; n--) {
			name[n].set_text(5 ,n*80, track[n].get_name_of_track());
			window.draw(name[n].text);
		}
	}
}
void set_button_size(bool is_checked[10], int &i, Button play[10], Button stop[10], Button del[10], Button check_t[10], Button check_f[10], Button &add_one, Button &play_all, Button &stop_rec) {
	if (i > 0) {
		for (int n = i-1; n >= 0; n--) {
			play[n].set_height(66); 			play[n].set_length(66);
			stop[n].set_height(66); 			stop[n].set_length(66);
			if (is_checked[n] == 1) {
				check_t[n].set_height(66); 			check_t[n].set_length(66);
				check_f[n].set_height(0); 			check_f[n].set_length(0);
			}
			if (is_checked[n] == 0){
				check_f[n].set_height(66); 			check_f[n].set_length(66);
				check_t[n].set_height(0); 			check_t[n].set_length(0);
			}
			del[n].set_height(66); 			del[n].set_length(66);
		}
	}
	add_one.set_height(213); 			add_one.set_length(213);
	play_all.set_height(213); 			play_all.set_length(213);
	stop_rec.set_height(213); 			stop_rec.set_length(213);
}
void draw_buttons (RenderWindow & window, bool is_checked[10], int &i, Button play[10], Button stop[10], Button del[10], Button check_t[10], Button check_f[10], Button &add_one, Button &play_all, Button &stop_rec) {
	if (i > 0) {
		for (int n = i-1; n >= 0; n--) {
			window.draw(play[n].sprite);
			window.draw(stop[n].sprite);
			if (is_checked[n] == 1)
				window.draw(check_t[n].sprite);
			if (is_checked[n] == 0)
				window.draw(check_f[n].sprite);
			window.draw(del[n].sprite);
		}
	}
	window.draw(add_one.sprite);
	window.draw(play_all.sprite);
	window.draw(stop_rec.sprite);
}
void it_is_working(RenderWindow & window, Name_text name[10], AudioTrack track[10], bool &is_record, bool is_checked[10], int &i, Button play[10], Button stop[10], Button del[10], Button check_t[10], Button check_f[10], Button &add_one, Button &play_all, Button &stop_rec) {
	if (add_one.is_pressed(window) == 1) {
		track[i].set_track_name();
		//track[i].set_track_number(i);
		for (int n = i - 1; n >= 0; n--) {
			if (is_checked[n] == 1)
				track[n].play_this_track();
		}
		track[i].start_rec();
		is_record = 1;
	}
	if (stop_rec.is_pressed(window) == 1 && is_record == 1) {
		for (int n = i - 1; n >= 0; n--) {
			track[n].stop_play();
		}
		track[i].stop_rec();
		is_record = 0;
		is_checked[i] = 1;
		i++;
	}
	if (play_all.is_pressed(window)==1) {
			for (int n = i - 1; n >= 0; n--) {
				if (is_checked[n] == 1)
					track[n].play_this_track();
			}
		}
	    for (int n = i-1; n >= 0; n--) {
	        if (play[n].is_pressed(window) == 1) {
		        track[n].play_this_track();
	        }
        }
		for (int n = i - 1; n >= 0; n--) {
			if (stop[n].is_pressed(window) == 1) {
				track[n].stop_play();
			}
		}
	for (int n = i - 1; n >= 0; n--) {
	if (check_t[n].is_pressed(window) == 1) {
		this_thread::sleep_for(std::chrono::milliseconds(300));
		is_checked[n] = 0;
	}
}
	for (int n = i - 1; n >= 0; n--) {
		if (check_f[n].is_pressed(window) == 1) {
			this_thread::sleep_for(std::chrono::milliseconds(300));
			is_checked[n] = 1;
		}
	}
	//for (int n = i - 1; n >= 0; n--) {
	//	if (del[n].is_pressed(window) == 1) {
	//		this_thread::sleep_for(std::chrono::milliseconds(300));
	//		for (int j = n; j < i; j++) {
	//			play[j] = play[j + 1];
	//			stop[j] = stop[j + 1];
	//			check_f[j] = check_f[j+1];
	//			check_t[j] = check_t[j + 1];
	//			del[j] = del[j+1];
	//			is_checked[j] = is_checked[j + 1];
	//			name[j] = name[j + 1];
	//			//track[j] = track[j + 1];
	//		}
	//		i--;
	//	}
	//}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int i = 0;
	bool is_checked[10], is_record = 0, is_playing = 0;
	for (int i = 0; i < 10; i++)
		is_checked[i] = 1;
	Name_text name[10];
	AudioTrack track[10];
	Button play[10], stop[10], del[10], check_t[10], check_f[10], add_one, play_all, stop_rec;
	RenderWindow window(VideoMode(1366, 768), "my_project", Style::Default);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		set_buttons_pos(is_checked, i, play, stop, del, check_t, check_f, add_one, play_all, stop_rec);
		set_button_sprite(window, is_checked, i, play, stop, del, check_t, check_f, add_one, play_all, stop_rec);
		set_button_size(is_checked, i, play, stop, del, check_t, check_f, add_one, play_all, stop_rec);
		window.clear();
		draw_buttons(window, is_checked, i, play, stop, del, check_t, check_f, add_one, play_all, stop_rec);
		set_text(name, track, window, i);
		window.display();
		it_is_working(window,name, track, is_record, is_checked, i, play, stop, del, check_t, check_f, add_one, play_all, stop_rec);
	}
}