//This program works with  *ppm files and changes the color of the image depending on the user's choice.

#include "Header.h"                                                   

void change_color_r(Solution& s, int r, int g, int b);
void change_color_g(Solution& s, int r, int g, int b);
void change_color_b(Solution& s, int r, int g, int b);
void change_color_bw(Solution& s, int r, int g, int b);

int main()
{
	Solution s;
	std::string file1 = "OldPicture.ppm", file2 = "NewPicture.ppm";

	s.image.open(file1);
	s.newimage.open(file2);

	if (s.check_open_file_error(s, file1, file2) == 1) return 1;

	std::string type, width, height, RGB;

	s.image >> type >> width >> height >> RGB;   // read information from image

	s.newimage << type << std::endl;             // write information to NEW image
	s.newimage << width << " " << height << std::endl;
	s.newimage << RGB << std::endl;

	char ans = s.users_choice();

	s.work_func(s, ans);

	return 0;
}

int Solution::check_open_file_error(Solution& s, std::string fname1, std::string fname2)
{
	if (!s.image.is_open())
	{
		std::cerr << "File '" << fname1 << "' didn't open!" << std::endl;
		return 1;
	}
	if (!s.newimage.is_open())
	{
		std::cerr << "File '" << fname2 << "' didn't open!" << std::endl;
		return 1;
	}
	return 0;
}

char Solution::users_choice()
{
	char answ;
	std::cout << "Please select an action and enter its number (1/2/3/4):" << std::endl << std::endl
		<< "1. Apply the red filter" << std::endl
		<< "2. Apply the green filter" << std::endl
		<< "3. Apply the blue filter" << std::endl
		<< "4. Apply a black and white filter" << std::endl << std::endl;

	std::cin >> answ;
	return answ;
}

void Solution::work_func(Solution& s, char ans)
{
	std::string red, green, blue;
	int r, g, b;

	//This pointer to a function can be replaced with std::function<void(...)>;
	void (*funct)(Solution& s, int r, int g, int b);
	switch (ans)
	{
	case '1': funct = change_color_r; break;
	case '2': funct = change_color_g; break;
	case '3': funct = change_color_b; break;
	case '4': funct = change_color_bw; break;
	default: return;
	}

	while (!image.eof())
	{
		image >> red >> green >> blue;

		std::stringstream redstr(red);
		std::stringstream greenstr(green);
		std::stringstream bluestr(blue);

		redstr >> r;
		greenstr >> g;
		bluestr >> b;

		funct(s, r, g, b);
	}
}

int Solution::temp(int x)
{
	return (x += 50) < 255 ? x : 255;
}

//Methods are declared outside the class, because declaring in the class alsoleads to a type error:
//a pointer to a bound function can only be used to call a function

void change_color_r(Solution& s, int r, int g, int b)
{
	s.newimage << s.temp(r) << " " << g << " " << b << std::endl;
}

void change_color_g(Solution& s, int r, int g, int b)
{
	s.newimage << r << " " << s.temp(g) << " " << b << std::endl;
}

void change_color_b(Solution& s, int r, int g, int b)
{
	s.newimage << r << " " << g << " " << s.temp(b) << std::endl;
}

void change_color_bw(Solution& s, int r, int g, int b)
{
	s.newimage << r << " " << r << " " << r << std::endl;
}
