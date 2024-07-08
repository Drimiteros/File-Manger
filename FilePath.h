#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "MouseCursor.h"
#include <locale>
#include <codecvt>
#include <future>
#include "FPS.h"

using namespace sf;
using namespace std;

class FileIcon
{
private:

public:
	Texture folderIocnTexture;
	Texture returnIcontexture;
	Texture musicIcontexture;
	Texture exeIcontexture;
	Texture txtIcontexture;
	Texture mp4Icontexture;
	Texture pngIcontexture;
	Sprite icon;
	FileIcon();
};

class FilePath
{
private:
	Font font;
	Font font2;
	Texture texture;

public:
	vector<Text> availablePathsText;
	vector<string> availablePathsString;
	vector<string> type;
	int size = 0;
	string oldPath;
	string getFileName;
	Text enterFilePathText;
	Text fileCountText;
	Text versionText;
	RectangleShape rec[2];
	Sprite sel;
	RectangleShape cover;
	RectangleShape itemView;
	Clock coverClock;

	FilePath();
	void findFile(string& enterFilePath, bool& isKeyPressed, bool& enter, MouseCursor& mc, FileIcon& folder, vector<FileIcon>& folders, bool& instructionClick, 
		int& scroll, int& scrollCounter, int& fileCount, int& theme, FPS& fps);
	void draw(RenderWindow& window, FileIcon& folder, vector<FileIcon>& folders, MouseCursor& mc, bool& isOpen);
};

class DiskSize
{
private:
	Font font;
	Font font2;
	int size = 4;
	Text* driveText = new Text[size];
	Text* driveInfoText = new Text[size];
	RectangleShape* bar = new RectangleShape[size];
	RectangleShape* bar2 = new RectangleShape[size];
	RectangleShape sel[2];
	string driveName;
	Sprite drive;
	Texture texture;
	Texture texture2;
	Clock clock;
	Clock selectClock;

public:
	DiskSize();
	void getDiskCount(DiskSize& ds, vector<DiskSize>& dss);
	void logic(vector<DiskSize>& dss, DiskSize& ds, FilePath& fp, vector<FilePath>& fps, MouseCursor& mc, string& enterFilePath, bool& enter, bool& isKeyPressed,
		FileIcon& f, vector <FileIcon>& fs, bool& instructionClick, int& scrollCounter, int& fileCount, int& theme);
	void draw(DiskSize& ds, vector<DiskSize>& dss, RenderWindow& window, MouseCursor& mc);
};
