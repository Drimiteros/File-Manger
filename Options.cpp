#include "Options.h"

Options::Options()
{
    font.loadFromFile("Files/Fonts/font.ttf");
    texture[0].loadFromFile("Files/Textures/sel3.png");
    texture[1].loadFromFile("Files/Textures/window.png");
    optionsText.setFont(font);
    optionsText.setCharacterSize(15);
    optionsText.setFillColor(Color::Black);
    optionsText.setPosition(630, 8);
    optionsText.setString("Options");

    closeText.setFont(font);
    closeText.setCharacterSize(15);
    closeText.setFillColor(Color::Black);
    closeText.setString("Close");

    for (int i = 0; i < 24; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(15);
        text[i].setFillColor(Color::Black);
        text[i].setPosition(530, 40);
    }

    sel.setTexture(texture[0]);
    optionsWindow.setTexture(texture[1]);
    optionsWindow.setOrigin(317 / 2, 360 / 2);

    arrowTexture[0].loadFromFile("Files/Textures/right.png");
    arrowTexture[1].loadFromFile("Files/Textures/left.png");
    arrow[0].setTexture(arrowTexture[0]);
    arrow[1].setTexture(arrowTexture[1]);
    arrow[0].setScale(0.1, 0.1);
    arrow[1].setScale(0.1, 0.1);

    lightTheme.setFillColor(Color::White);
    lightTheme.setOutlineColor(Color::Black);
    lightTheme.setOutlineThickness(1);
    lightTheme.setSize(Vector2f(20, 20));
    darkTheme.setFillColor(Color(70, 73, 87));
    darkTheme.setOutlineColor(Color::Black);
    darkTheme.setOutlineThickness(1);
    darkTheme.setSize(Vector2f(20, 20));
}

void Options::scaleMenu(FilePath& fp, vector <FilePath>& fps, FileIcon& fi, vector<FileIcon>& fis, int& scrollCounter, int& scroll, 
    MouseCursor& mc, bool& isOpen, Color& appliedColor, int& theme)
{
    if (mc.cursor.getGlobalBounds().intersects(optionsText.getGlobalBounds()))
    {
        sel.setPosition(optionsText.getPosition().x - 23, optionsText.getPosition().y - 3);
        optionsText.setFillColor(Color::White);
    }
    else if (mc.cursor.getGlobalBounds().intersects(closeText.getGlobalBounds()))
    {
        sel.setPosition(closeText.getPosition().x - 28, closeText.getPosition().y - 3);
        closeText.setFillColor(Color::White);
    }
    else
    {
        sel.setPosition(99999, 99999);
        closeText.setFillColor(Color::Black);
        optionsText.setFillColor(Color::Black);
    }

    if (mc.cursor.getGlobalBounds().intersects(optionsText.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        isOpen = true;
    if (mc.cursor.getGlobalBounds().intersects(closeText.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        isOpen = false;
    if (isOpen == true)
    {
        optionsWindow.setPosition((600 / 2) + 355, (600 / 2) - 80);
        closeText.setPosition(optionsWindow.getPosition().x - 20, optionsWindow.getPosition().y + 150);
        text[0].setPosition(optionsWindow.getPosition().x - 150, optionsWindow.getPosition().y - 100);
        text[0].setString("Theme: ");
        text[1].setPosition(optionsWindow.getPosition().x - 150, optionsWindow.getPosition().y - 130);
        text[1].setString("UI Scale: " + to_string(scaleVal) + "%");
        arrow[1].setPosition(optionsWindow.getPosition().x - 55, optionsWindow.getPosition().y - 130);
        arrow[0].setPosition(optionsWindow.getPosition().x - 20, optionsWindow.getPosition().y - 130);
        lightTheme.setPosition(optionsWindow.getPosition().x - 55, optionsWindow.getPosition().y - 100);
        darkTheme.setPosition(optionsWindow.getPosition().x - 20, optionsWindow.getPosition().y - 100);
        Color whiteColor(255, 255, 255);
        Color darkColor(70, 73, 87);

        if (mc.cursor.getGlobalBounds().intersects(lightTheme.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        {
            appliedColor = whiteColor;
            theme = 0;
        }
        if (mc.cursor.getGlobalBounds().intersects(darkTheme.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        {
            appliedColor = darkColor;
            theme = 1;
        }

        if (arrow[0].getGlobalBounds().intersects(mc.cursor.getGlobalBounds()))
            arrow[0].setColor(Color::Cyan);
        else
            arrow[0].setColor(Color(255, 255, 255));
        if (arrow[1].getGlobalBounds().intersects(mc.cursor.getGlobalBounds()))
            arrow[1].setColor(Color::Cyan);
        else
            arrow[1].setColor(Color(255, 255, 255));

        if (mc.cursor.getGlobalBounds().intersects(arrow[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)
            && scaleClock.getElapsedTime().asSeconds() > 0.1 && scaleVal < 100)
        {
            scaleClock.restart();
            scale[0] = scale[0] + 0.01;
            scale[1] = scale[1] + 0.1;
            scale[2] = scale[2] + 1;
            scale[3] = scale[3] + 3;
            scale[4] = scale[4] + 1.05;
            scaleVal = scaleVal + 10;
        }
        if (mc.cursor.getGlobalBounds().intersects(arrow[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)
            && scaleClock.getElapsedTime().asSeconds() > 0.1 && scaleVal > 0)
        {
            scaleClock.restart();
            scale[0] = scale[0] - 0.01;
            scale[1] = scale[1] - 0.1;
            scale[2] = scale[2] - 1;
            scale[3] = scale[3] - 3;
            scale[4] = scale[4] - 1.1;
            scaleVal = scaleVal - 10;
        }
    }
    if (isOpen == false)
    {
        optionsWindow.setPosition(99999, 99999);
        closeText.setPosition(99999, 99999);
        text[0].setPosition(99999, 99999);
        text[1].setPosition(99999, 99999);
        arrow[1].setPosition(99999, 99999);
        arrow[0].setPosition(99999, 99999);
        lightTheme.setPosition(99999, 99999);
        darkTheme.setPosition(99999, 99999);
    }

    if (scroll == 1 && scrollCounter < 0)
    {
        scrollCounter = scrollCounter + (24 + scale[3]);
        scroll = 0;
    }
    else if (scroll == -1)
    {
        scrollCounter = scrollCounter - (24 + scale[3]);
        scroll = 0;
    }

    fp.sel.setScale(1, 1 + scale[1]);
    for (int i = 0; i < fis.size(); i++)
    {
        fis[i].icon.setScale(0.1 + scale[0], 0.1 + scale[0]);
        fis[i].icon.setPosition(10, 150 + 47 + (i * (24 + scale[3])) + scrollCounter);
    }
    for (int a = 0; a < fp.availablePathsString.size(); a++)
    {
        fp.availablePathsText[a].setCharacterSize(13 + scale[2]);
        fp.availablePathsText[a].setPosition(40 + scale[3], 200 + (a * (24 + scale[3])) + scrollCounter);
    }
}

void Options::draw(RenderWindow& window)
{
    window.draw(optionsWindow);
    window.draw(sel);
    window.draw(optionsText);
    window.draw(closeText);
    window.draw(arrow[0]);
    window.draw(arrow[1]);
    window.draw(lightTheme);
    window.draw(darkTheme);
    for (int i = 0; i < 24; i++)
        window.draw(text[i]);
}