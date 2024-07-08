#include "FilePath.h"

FileIcon::FileIcon()
{
    folderIocnTexture.loadFromFile("Files/Textures/folder.png");
    returnIcontexture.loadFromFile("Files/Textures/arrow.png");
    musicIcontexture.loadFromFile("Files/Textures/note.png");
    exeIcontexture.loadFromFile("Files/Textures/file.png");
    txtIcontexture.loadFromFile("Files/Textures/txt.png");
    mp4Icontexture.loadFromFile("Files/Textures/video.png");
    pngIcontexture.loadFromFile("Files/Textures/image.png");
}

//DISK SIZE
DiskSize::DiskSize()
{
    font.loadFromFile("Files/Fonts/font.ttf");
    font2.loadFromFile("Files/Fonts/font2.ttf");
    for (int i = 0; i < size; i++)
    {
        driveText[i].setFont(font2);
        driveText[i].setCharacterSize(25);
        driveInfoText[i].setFont(font);
        driveInfoText[i].setCharacterSize(10);
        bar[i].setFillColor(Color::Blue);
        bar2[i].setSize(Vector2f(80, 15));
        bar2[i].setFillColor(Color(5, 97, 255, 150));
        driveText[i].setFillColor(Color::Black);
        driveInfoText[i].setFillColor(Color::Black);
    }
    driveText[0].setPosition(50, 70);
    driveInfoText[0].setPosition(10, 80 + 25 + 15);
    bar[0].setPosition(10, 85 + 15);
    bar2[0].setPosition(10, 85 + 15);
    driveText[1].setPosition(150, 70);
    driveInfoText[1].setPosition(100 + 10, 80 + 25 + 15);
    bar[1].setPosition(100 + 10, 85 + 15);
    bar2[1].setPosition(100 + 10, 85 + 15);
    driveText[2].setPosition(252, 50 + 20);
    driveInfoText[2].setPosition(190 + 20, 80 + 25 + 15);
    bar[2].setPosition(190 + 20, 85 + 15);
    bar2[2].setPosition(190 + 20, 85 + 15);
    driveText[3].setPosition(353, 50 + 20);
    driveInfoText[3].setPosition(280 + 30, 80 + 25 + 15);
    bar[3].setPosition(280 + 30, 85 + 15);
    bar2[3].setPosition(280 + 30, 85 + 15);

    texture.loadFromFile("Files/Textures/drive.png");
    drive.setTexture(texture);
    drive.setScale(0.19, 0.19);

    texture2.loadFromFile("Files/Textures/sel.png");
    sel[1].setSize(Vector2f(90, 140));
    sel[0].setSize(Vector2f(90, 140));
    //sel[0].setOutlineColor(Color::Blue);
    //sel[0].setOutlineThickness(2);
    sel[0].setFillColor(Color(255, 255, 255, 150));
    sel[0].setTexture(&texture2);
}

void DiskSize::getDiskCount(DiskSize& ds, vector<DiskSize>& dss)
{
    DWORD drivesBufferLength = GetLogicalDriveStrings(0, nullptr);
    vector<wchar_t> drivesBuffer(drivesBufferLength);
    GetLogicalDriveStrings(drivesBufferLength, &drivesBuffer[0]);

    wchar_t* drive = &drivesBuffer[0];
    while (*drive)
    {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        string driveLetter = converter.to_bytes(drive);
        driveName = driveLetter;
        drive += wcslen(drive) + 1;
        dss.push_back(DiskSize(ds));
    }
}

void DiskSize::logic(vector<DiskSize>& dss, DiskSize& ds, FilePath& fp, vector<FilePath>& fps, MouseCursor& mc, string& enterFilePath, bool& enter, bool& isKeyPressed,
    FileIcon& f, vector <FileIcon>& fs, bool& instructionClick, int& scrollCounter, int& fileCount, int& theme)
{
    //GET DRIVE INFO
    DWORD drivesBufferLength = GetLogicalDriveStrings(0, nullptr);
    vector<wchar_t> drivesBuffer(drivesBufferLength);
    GetLogicalDriveStrings(drivesBufferLength, &drivesBuffer[0]);

    wchar_t* drive = &drivesBuffer[0];
    while (*drive)
    {
        ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
        if (GetDiskFreeSpaceExW(drive, &freeBytesAvailable, &totalBytes, &totalFreeBytes))
        {
            double totalSize = static_cast<double>(totalBytes.QuadPart) / (1024 * 1024 * 1024);
            double freeSize = static_cast<double>(totalFreeBytes.QuadPart) / (1024 * 1024 * 1024);
            double usedSize = totalSize - freeSize;

            int freeSizeBar = (freeSize * 80) / totalSize;
            int usedSizeBar = ((totalSize - freeSize) * 80) / totalSize;
            int freeSizePercentage = (freeSize * 100) / totalSize;
            int usedSizePercentage = ((totalSize - freeSize) * 100) / totalSize;

            if (*drive == L'C')
            {
                driveText[0].setString(drive);
                driveInfoText[0].setString("Total Size: " + to_string(int(totalSize)) + " GB\nUsed Size: " + to_string(int(usedSize))
                    + " GB\nFree Size: " + to_string(int(freeSize)) + " GB\nFree: " + to_string(freeSizePercentage) + " %\nUsed: " + to_string(usedSizePercentage) + "%");
                if ((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar > usedSizeBar)
                    bar[0].setSize(Vector2f(usedSizeBar, 15));
                if (clock.getElapsedTime().asSeconds() > 0 && (clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar <= usedSizeBar && bar[0].getSize().x <= 80)
                {
                    bar[0].setSize(Vector2f((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar, 15));
                    bar[0].setFillColor(Color((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.009)) / usedSizeBar, 255 - (clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.009)) / usedSizeBar, 0, 255));
                }
            }
            if (*drive == L'D')
            {
                driveText[1].setString(drive);
                driveInfoText[1].setString("Total Size: " + to_string(int(totalSize)) + " GB\nUsed Size: " + to_string(int(usedSize))
                    + " GB\nFree Size: " + to_string(int(freeSize)) + " GB\nFree: " + to_string(freeSizePercentage) + " %\nUsed: " + to_string(usedSizePercentage) + "%");
                if ((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar > usedSizeBar)
                    bar[1].setSize(Vector2f(usedSizeBar, 15));
                if (clock.getElapsedTime().asSeconds() > 0 && (clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar <= usedSizeBar && bar[0].getSize().x <= 80)
                {
                    bar[1].setSize(Vector2f((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar, 15));
                    bar[1].setFillColor(Color((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.009)) / usedSizeBar, 255 - (clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.009)) / usedSizeBar, 0, 255));
                }
            }
            if (*drive == L'E')
            {
                driveText[2].setString(drive);
                driveInfoText[2].setString("Total Size: " + to_string(int(totalSize)) + " GB\nUsed Size: " + to_string(int(usedSize))
                    + " GB\nFree Size: " + to_string(int(freeSize)) + " GB\nFree: " + to_string(freeSizePercentage) + " %\nUsed: " + to_string(usedSizePercentage) + "%");
                if ((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar > usedSizeBar)
                    bar[2].setSize(Vector2f(usedSizeBar, 15));
                if (clock.getElapsedTime().asSeconds() > 0 && (clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar <= usedSizeBar && bar[0].getSize().x <= 80)
                {
                    bar[2].setSize(Vector2f((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar, 15));
                    bar[2].setFillColor(Color((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.009)) / usedSizeBar, 255 - (clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.009)) / usedSizeBar, 0, 255));
                }
            }
            if (*drive == L'F')
            {
                driveText[3].setString(drive);
                driveInfoText[3].setString("Total Size: " + to_string(int(totalSize)) + " GB\nUsed Size: " + to_string(int(usedSize))
                    + " GB\nFree Size: " + to_string(int(freeSize)) + " GB\nFree: " + to_string(freeSizePercentage) + " %\nUsed: " + to_string(usedSizePercentage) + "%");
                if ((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar > usedSizeBar)
                    bar[3].setSize(Vector2f(usedSizeBar, 15));
                if (clock.getElapsedTime().asSeconds() > 0 && (clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar <= usedSizeBar && bar[0].getSize().x <= 80)
                {
                    bar[3].setSize(Vector2f((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.003)) / usedSizeBar, 15));
                    bar[3].setFillColor(Color((clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.009)) / usedSizeBar, 255 - (clock.getElapsedTime().asMilliseconds() * (3 * clock.getElapsedTime().asMilliseconds() * 0.009)) / usedSizeBar, 0, 255));
                }
            }
        }
        drive += wcslen(drive) + 1;
    }

    //SELECT PATH
    for (int i = 0; i < dss.size(); i++)
    {
        if (mc.cursor.getGlobalBounds().intersects(dss[i].sel[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && selectClock.getElapsedTime().asSeconds() > 0.2)
        {
            enterFilePath = dss[i].driveName;
            enter = true;
            fp.availablePathsString.clear();
            fp.availablePathsText.clear();
            fs.clear();
            fp.type.clear();
            selectClock.restart();
            instructionClick = true;
            fp.coverClock.restart();
            scrollCounter = 0;
            fileCount = 0;
        }
    }

    //THEME
    for (int i = 0; i < size; i++)
    {
        if (theme == 0)
        {
            driveText[i].setFillColor(Color::Black);
            driveInfoText[i].setFillColor(Color::Black);
        }
        if (theme == 1)
        {
            driveText[i].setFillColor(Color::White);
            driveInfoText[i].setFillColor(Color::White);
        }
    }
}

void DiskSize::draw(DiskSize& ds, vector<DiskSize>& dss, RenderWindow& window, MouseCursor& mc)
{
    mc.state = 0;
    for (int i = 0; i < dss.size(); i++)
    {
        if (mc.cursor.getGlobalBounds().intersects(dss[i].sel[1].getGlobalBounds()))
        {
            dss[i].sel[0].setPosition(dss[i].drive.getPosition().x - 5, dss[i].drive.getPosition().y - 10);
            window.draw(dss[i].sel[0]);
            mc.state = 1;
        }
    }
    for (int i = 0; i < size; i++)
    {
        window.draw(driveText[i]);
        window.draw(driveInfoText[i]);
        window.draw(bar2[i]);
        window.draw(bar[i]);
    }
    for (int i = 0; i < dss.size(); i++)
    {
        dss[i].drive.setPosition(10 + (100 * i), 53);
        dss[i].sel[1].setPosition(10 + (100 * i), 55);
        window.draw(dss[i].drive);
    }
}

//FILE PATH
FilePath::FilePath()
{
    texture.loadFromFile("Files/Textures/sel2.png");
    font.loadFromFile("Files/Fonts/font.ttf");
    font2.loadFromFile("Files/Fonts/font2.ttf");
    enterFilePathText.setFont(font2);
    enterFilePathText.setPosition(10, 10);
    enterFilePathText.setCharacterSize(15);
    enterFilePathText.setFillColor(Color(0, 0, 0));
    rec[0].setFillColor(Color(61, 61, 61, 50));
    rec[0].setSize(Vector2f(590, 25));
    rec[0].setPosition(5, 5);
    rec[1].setFillColor(Color(0, 0, 0, 200));
    rec[1].setSize(Vector2f(590, 1));
    rec[1].setPosition(5, 30);
    sel.setTexture(texture);
    cover.setSize(Vector2f(700, 500));
    cover.setFillColor(Color::White);
    itemView.setSize(Vector2f(450, 370));
    itemView.setFillColor(Color(255, 0, 0, 100));
    itemView.setPosition(5, 198);
    fileCountText.setFont(font2);
    fileCountText.setCharacterSize(15);
    fileCountText.setPosition(10, 590);
    fileCountText.setFillColor(Color::Black);
    versionText.setFont(font2);
    versionText.setCharacterSize(15);
    versionText.setPosition(810, 590);
    versionText.setFillColor(Color::Black);
    versionText.setString("Version 1.1");
}

void FilePath::findFile(string& enterFilePath, bool& isKeyPressed, bool& enter, MouseCursor& mc, FileIcon& icon, vector<FileIcon>& icons, bool& instructionClick,
    int& scroll, int& scrollCounter, int& fileCount, int& theme, FPS& fps)
{
    availablePathsString.reserve(140);
    availablePathsText.reserve(140);
    icons.reserve(140);
    type.reserve(140);

    //ASSIGN enterFilePath to enterFilePathText
    enterFilePathText.setString(enterFilePath);

    if ((enter == true && oldPath != enterFilePath) || instructionClick == true)
    {
        //FIND FILE
        WIN32_FIND_DATAA findData;
        HANDLE hFind = FindFirstFileA((enterFilePath + "\\*").c_str(), &findData);

        instructionClick = false;
        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("Folder");
                    fileCount++;
                }
                if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".lnk")
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("Shortcut");
                    fileCount++;
                }
                else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".mp3")
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("Audio");
                    fileCount++;
                }
                else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".wav")
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("Audio");
                    fileCount++;
                }
                else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".png")
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("Image");
                    fileCount++;
                }
                else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".jpg")
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("Image");
                    fileCount++;
                }
                else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".exe")
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("App");
                    fileCount++;
                }
                else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".txt")
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("Txt");
                    fileCount++;
                }
                else if (string(findData.cFileName).length() >= 4 && string(findData.cFileName).substr(string(findData.cFileName).length() - 4) == ".mp4")
                {
                    availablePathsString.emplace_back(findData.cFileName);
                    availablePathsText.emplace_back(Text());
                    icons.emplace_back(FileIcon(icon));
                    type.emplace_back("Video");
                    fileCount++;
                }
                else if (string(findData.cFileName).length() >= 2 && string(findData.cFileName).substr(string(findData.cFileName).length() - 2) == "..")
                    fileCount--;
                enter = false;
                oldPath = enterFilePath;
            } while (FindNextFileA(hFind, &findData) != 0);

            FindClose(hFind);
        }
    }
    if (isKeyPressed == true)
    {
        coverClock.restart();
        availablePathsString.clear();
        availablePathsText.clear();
        icons.clear();
        type.clear();
        fileCount = 0;
    }
    for (int i = 0; i < availablePathsString.size(); i++)
    {
        availablePathsText[i].setFont(font);
        availablePathsText[i].setString(availablePathsString[i]);

        //EXECUTE FILE
        if (mc.cursor.getGlobalBounds().intersects(availablePathsText[i].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)
            && mc.selectedClock.getElapsedTime().asSeconds() > 0.3)
            mc.selected = true;
        if (mc.selected == true)
        {
            if (type[i].find("Folder") != string::npos)
            {
                enterFilePath += availablePathsString[i] + "\\";
                mc.selected = false;
                enter = true;
                scrollCounter = 0;
                mc.selectedClock.restart();
                coverClock.restart();
                availablePathsString.clear();
                availablePathsText.clear();
                icons.clear();
                type.clear();
                fileCount = 0;
                break;
            }
            if (type[i].find("Audio") != string::npos || type[i].find("Video") != string::npos
                || type[i].find("Txt") != string::npos || type[i].find("Shortcut") != string::npos
                || type[i].find("Image") != string::npos)
            {
                enterFilePath = enterFilePath;
                string comm = "\"\"" + enterFilePath + availablePathsString[i] + "\"";
                system(comm.c_str());
                mc.selected = false;
                enter = false;
                scrollCounter = 0;
            }
            if (type[i].find("App") != string::npos)
            {
                enterFilePath = enterFilePath;
                wstring comm = L"" + enterFilePath + availablePathsString[i] + L" > NUL 2>&1";

                //CREATING A NEW PROCCESS TO HANDLE THE EXECUTABLES
                // Set up the STARTUPINFO structure to specify redirection
                STARTUPINFO startupInfo = { sizeof(startupInfo) };
                startupInfo.dwFlags = STARTF_USESHOWWINDOW;

                // Create a PROCESS_INFORMATION structure to receive information about the new process
                PROCESS_INFORMATION processInfo;

                // Use CreateProcess to launch the .exe with the specified redirection and options
                if (CreateProcess(NULL, &comm[0], NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
                    // Close the handles to the new process and thread to avoid resource leaks
                    CloseHandle(processInfo.hProcess);
                    CloseHandle(processInfo.hThread);
                }

                mc.selected = false;
                enter = false;
                scrollCounter = 0;
            }
        }
    }

    //ANIMATE
    if (coverClock.getElapsedTime().asSeconds() <= 0.4)
        cover.setPosition(0, 190);
    else
        cover.move(0, 18 * fps.time.asSeconds() * 60);

    //INIT FILE ICON
    for (int i = 0; i < icons.size(); i++)
    {
        string fileType = availablePathsText[i].getString();
        size_t foundEXE = fileType.find(".exe");
        size_t foundLNK = fileType.find(".lnk");
        size_t foundWAV = fileType.find(".wav");
        size_t foundMP3 = fileType.find(".mp3");
        size_t foundTXT = fileType.find(".txt");
        size_t foundMP4 = fileType.find(".mp4");
        size_t foundPNG = fileType.find(".png");
        size_t foundJPG = fileType.find(".jpg");

        if (availablePathsText[i].getString() == "..")
            icons[i].icon.setTexture(icon.returnIcontexture);
        else if (foundWAV != string::npos || foundMP3 != string::npos)
            icons[i].icon.setTexture(icon.musicIcontexture);
        else if (foundEXE != string::npos || foundLNK != string::npos)
            icons[i].icon.setTexture(icon.exeIcontexture);
        else if (foundTXT != string::npos)
            icons[i].icon.setTexture(icon.txtIcontexture);
        else if (foundMP4 != string::npos)
            icons[i].icon.setTexture(icon.mp4Icontexture);
        else if (foundPNG != string::npos || foundJPG != string::npos)
            icons[i].icon.setTexture(icon.pngIcontexture);
        else
            icons[i].icon.setTexture(icon.folderIocnTexture);
    }

    //INIT FILE COUNT
    fileCountText.setString("Files: " + to_string(fileCount));

    //THEME
    for (int i = 0; i < availablePathsText.size(); i++)
    {
        if (theme == 0)
        {
            if (mc.cursor.getGlobalBounds().intersects(availablePathsText[i].getGlobalBounds()))
            {
                availablePathsText[i].setFillColor(Color::White);
                mc.state = 1;
            }
            else
            {
                availablePathsText[i].setFillColor(Color::Black);
                availablePathsText[i].setOutlineThickness(0);
            }
            cover.setFillColor(Color::White);
            fileCountText.setFillColor(Color::Black);
        }
        if (theme == 1)
        {
            availablePathsText[i].setFillColor(Color::White);
            cover.setFillColor(Color(70, 73, 87));
            fileCountText.setFillColor(Color::White);
        }
    }
}

void FilePath::draw(RenderWindow& window, FileIcon& icon, vector<FileIcon>& icons, MouseCursor& mc, bool& isOpen)
{
    window.draw(rec[0]);
    window.draw(rec[1]);
    for (int i = 0; i < availablePathsText.size(); i++)
    {
        if (availablePathsText[i].getGlobalBounds().intersects(itemView.getGlobalBounds()))
        {
            if (mc.cursor.getGlobalBounds().intersects(availablePathsText[i].getGlobalBounds()) && isOpen == false)
            {
                sel.setPosition(availablePathsText[i].getPosition().x - 100, availablePathsText[i].getPosition().y - 5);
                window.draw(sel);
            }
            window.draw(availablePathsText[i]);
        }
    }
    for (int i = 0; i < icons.size(); i++)
    {
        if (icons[i].icon.getGlobalBounds().intersects(itemView.getGlobalBounds()))
            window.draw(icons[i].icon);
    }
    window.draw(enterFilePathText);
    window.draw(cover);
    //window.draw(itemView);
    window.draw(fileCountText);
    window.draw(versionText);
}