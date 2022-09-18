#pragma once
#include <SFML/Graphics.hpp>

#include <iostream> 
#include <vector> 
#include <list>
#include <thread> 
#include "Macros.h"

template<class ownerClass> class GUI; 
class Button;
class Screen;

class Button : public sf::Text
{
private:
	sf::Font text_font;
	sf::Color color_when_selected;
	sf::Color color_when_unselected;
public:
	bool triggered = false;
	Button(
		std::string text,
		sf::Color color_when_selected,
		sf::Color color_when_unselected,
		int characterSize,
		sf::Vector2f pos,
		std::string text_font_file = CHESS_ARIAL_FONT_FILE
	);

	void Select();
	void Unselect();
	void onClicked();

};

class Screen
{
private : 
	std::vector<Button*>screen_components;	
	std::vector<sf::Text>screen_texts;
	unsigned int selectedButton;
	sf::RenderWindow* render_window = nullptr; 
	sf::Event* eventHolder = nullptr;	

	sf::Color clearing_color;
public : 
	Screen(sf::RenderWindow* window, sf::Event* eventHolder_,sf::Color clearingColor_ = sf::Color::White) : render_window(window), eventHolder(eventHolder_), clearing_color(clearingColor_){};
	void AddComponent(Button* button); 
	void AddComponent(sf::Text text);
	Button* GiveButton(unsigned int button_index) { return screen_components[button_index]; };
	sf::Text& GiveText(unsigned int text_index) { return screen_texts[text_index]; };
	virtual void Display();
};

template <class owner_class> class GameScreen : public Screen
{
private : 
	owner_class* object = nullptr; 
	void(owner_class::* function)(void) = nullptr;
public : 
	GameScreen(owner_class* object_, void(owner_class::* function_)(void)) : Screen(nullptr,nullptr) , object(object_), function(function_) {};
	void Display() override
	{
		(object->*function)();
	};
};

template<class ownerClass> class GUI
{
	struct TriggerMechanism
	{
		Button* triggerObject = nullptr;
		ownerClass* triggeredObject = nullptr;
		void(ownerClass::* triggeredFunction)(void) = nullptr;
	};
private : 
	sf::RenderWindow* window = nullptr; 
	std::vector<TriggerMechanism>BindedObjects;
	void CheckForTrigger()
	{
		if (BindedObjects.size() == 0)
			return; 

		for (TriggerMechanism& mec : BindedObjects)
		{
			if (mec.triggerObject->triggered == true)
			{
				(mec.triggeredObject->*mec.triggeredFunction)();
				mec.triggerObject->triggered = false;
			}
		}
	}

	std::vector<Screen*>screens;
	unsigned int selectedScreen;
public :
	GUI(sf::RenderWindow* render_window, sf::Event* eventHolder) : window(render_window) {};
	void AddScreen(Screen* screen)
	{
		screens.push_back(screen);
		if (screens.size() == 1)
			selectedScreen = 0; 
	}
	void BindObjects(Button* triggerObject, ownerClass* triggeredObject, void(ownerClass::* triggeredFunction)(void))
	{		
		GUI::TriggerMechanism mec; 
		mec.triggerObject = triggerObject; 
		mec.triggeredObject = triggeredObject; 
		mec.triggeredFunction = triggeredFunction; 
		BindedObjects.push_back(mec);
	}
	void ChangeScreen(unsigned int screen_index)
	{
		selectedScreen = screen_index;
	};
	void Display()
	{
		while (window->isOpen())
		{
			if (screens.size() == 0)
				continue; 
			else
			{
				screens[selectedScreen]->Display();
				CheckForTrigger();
			}
		}
	}

	Screen* GiveScreen(unsigned int screen_index) { return screens[screen_index]; };
};