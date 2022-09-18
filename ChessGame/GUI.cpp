#include "GUI.h"

Button::Button(std::string text, sf::Color color_when_selected, sf::Color color_when_unselected, int characterSize, sf::Vector2f pos,std::string text_font_file)
{
	setString(text); 
	this->color_when_selected = color_when_selected; 
	this->color_when_unselected = color_when_unselected; 
	setFillColor(color_when_unselected);
	setCharacterSize(characterSize); 
	setPosition(pos);
	text_font.loadFromFile(text_font_file); 
	setFont(text_font);

}

void Button::Select()
{
	setFillColor(color_when_selected);
}

void Button::Unselect()
{
	setFillColor(color_when_unselected);
}

void Button::onClicked()
{
	triggered = true;
}

void Screen::AddComponent(Button* button)
{
	screen_components.push_back(button);
	if (screen_components.size() == 1)
	{
		selectedButton = 0;
		button->Select();
	}
}

void Screen::AddComponent(sf::Text text)
{
	screen_texts.push_back(text);
}

void Screen::Display()
{
	while (render_window->pollEvent(*eventHolder))
	{
		switch (eventHolder->type)
		{
		case sf::Event::KeyPressed: 
			switch (eventHolder->key.code)
			{
				case sf::Keyboard::Up : 
					if (selectedButton == 0)
					{
						screen_components[selectedButton]->Unselect();
						selectedButton = screen_components.size() - 1;
						screen_components[selectedButton]->Select();
					}
					else if (screen_components.size() == 0)
					{
						break;
					}
					else
					{
						screen_components[selectedButton]->Unselect();
						selectedButton--;
						screen_components[selectedButton]->Select();
					}
					break;
				case sf::Keyboard::Down: 
					if (selectedButton == screen_components.size() - 1)
					{
						screen_components[selectedButton]->Unselect();
						selectedButton = 0;
						screen_components[selectedButton]->Select();;
					}
					else if (screen_components.size() == 0)
					{
						break;
					}
					else
					{
						screen_components[selectedButton]->Unselect();
						selectedButton++;
						screen_components[selectedButton]->Select();
					}
					break;
				case sf::Keyboard::Enter : 

					if (screen_components.size() == 0)
					{
						break;
					}
					else
					{
						screen_components[selectedButton]->onClicked();
					}
					break;
			}
			break;
		case sf::Event::Closed: 
			exit(0); 			
		}
	}

	render_window->clear(clearing_color); 
	for (int a = 0; a < screen_components.size(); a++)
	{
		render_window->draw(*screen_components[a]);
	}

	for (int a = 0; a < screen_texts.size(); a++)
	{
		render_window->draw(screen_texts[a]);
	}
	render_window->display();

}

