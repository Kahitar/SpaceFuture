#include "TextBox.hpp"
#include "Framework.hpp"

TextBox::TextBox(std::string text, sf::Vector2f position, std::string FontPath,
                 int borderThickness, sf::Color fillColor, sf::Color outlineColor)
{
    setFont(FontPath);
    setText(text);
    setPosition(position);
    setBorderThickness(borderThickness);
    setFillColor(fillColor);
    setOutlineColor(outlineColor);
}

TextBox::~TextBox()
{
    //dtor
}

// Setter //
void TextBox::setScale(float x, float y)
{
    throw "Not implemented";
}

void TextBox::setSize(sf::Vector2f size)
{
    mText.setCharacterSize(size.x);
}

void TextBox::setText(std::string text)
{
    mText.setString(text);
    mBorder.setSize(sf::Vector2f(mText.getGlobalBounds().width + 10,mText.getGlobalBounds().height + 5));
    this->setPosition(mPos);
}

void TextBox::setFont(std::string fontPath)
{
    font.loadFromFile(fontPath);
    mText.setFont(font);
}

void TextBox::setPosition(sf::Vector2f position)
{
    mBorder.setPosition(sf::Vector2f(position.x - 5,position.y));
    mText.setPosition(position);
    mPos = position;
}

void TextBox::setBorderThickness(int borderThickness)
{
    mBorder.setOutlineThickness(borderThickness);
}

void TextBox::setFillColor(sf::Color fillColor)
{
    mBorder.setFillColor(fillColor);
}

void TextBox::setOutlineColor(sf::Color outlineColor)
{
    mBorder.setOutlineColor(outlineColor);
}


// Getter //
std::string TextBox::getText()
{
    return mText.getString();
    //TODO: Test if this returns a copy of the Text or a reference to it, since "getString()" returns a reference
}

sf::FloatRect TextBox::getGlobalBounds()
{
    return mBorder.getGlobalBounds();
}



void TextBox::update(Framework &frmwrk)
{

}

void TextBox::handle(Framework &frmwrk)
{

}

void TextBox::render(Framework &frmwrk)
{
    frmwrk.spRenderWindow->draw(mBorder);
	frmwrk.spRenderWindow->draw(mText);
}
