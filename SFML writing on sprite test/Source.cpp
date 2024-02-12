#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::Text userInputText;
	userInputText.setCharacterSize(24);
	userInputText.setFillColor(sf::Color::Red);
	sf::String userInput;
	userInputText.setPosition(650, 235);
	std::string projectFolderPath = "./"; // Assuming the project folder is the working directory

	sf::Texture add_mew_worker_texture;
	std::string add_new_worker_path = projectFolderPath + "resources/add_new_worker.png";
	add_mew_worker_texture.loadFromFile(add_new_worker_path);

	sf::Texture select_ui_1_texture;
	std::string select_ui_1_path = projectFolderPath + "resources/select_ui_1.png";
	select_ui_1_texture.loadFromFile(select_ui_1_path);

	sf::Texture check_mark_texture;
	std::string check_mark_path = projectFolderPath + "resources/check_mark.png";
	check_mark_texture.loadFromFile(check_mark_path);

	sf::Texture check_mark_1_texture;
	std::string check_mark_1_path = projectFolderPath + "resources/check_mark.png";
	check_mark_1_texture.loadFromFile(check_mark_1_path);

	sf::Sprite add_new_worker_sprite;
	add_new_worker_sprite.setTexture(add_mew_worker_texture);
	add_new_worker_sprite.setPosition(0, 0);
	add_new_worker_sprite.setScale(1, 1);

	sf::Sprite select_ui_1_sprite;
	select_ui_1_sprite.setTexture(select_ui_1_texture);
	select_ui_1_sprite.setPosition(650, 175);
	select_ui_1_sprite.setScale(0.3, 0.05);

	sf::Sprite check_mark_sprite;
	check_mark_sprite.setTexture(check_mark_1_texture);
	check_mark_sprite.setPosition(555, 395);
	check_mark_sprite.setScale(1, 1);

	sf::Sprite check_mark_1_sprite;
	check_mark_1_sprite.setTexture(check_mark_1_texture);
	check_mark_1_sprite.setPosition(555, 660);
	check_mark_1_sprite.setScale(1, 1);

	bool movedown = false;
	bool moveup = false;
	bool confirm = false;

	enum menu_state
	{
		new_worker_type,
		new_worker_type_1,
		new_worker_check,
		new_worker_check_1,
	};

	int menu_state = new_worker_type;


	sf::RenderWindow window(sf::VideoMode(1680, 1050), "Writing on sprite");
	window.setFramerateLimit(144);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::EventType::KeyPressed)
			{

				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					// Handle moving up
					moveup = true;
					break;

				case sf::Keyboard::Down:
					// Handle moving down
					movedown = true;
					break;
				case sf::Keyboard::Enter:
					// Handle path comfrimmation
					confirm = true;
					break;
				}
			}
			else if (event.type == sf::Event::EventType::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					moveup = false;
					break;

				case sf::Keyboard::Down:
					movedown = false;
					break;
				case sf::Keyboard::Enter:
					confirm = false;
					break;

				}
			}
			if (menu_state == new_worker_type && confirm && select_ui_1_sprite.getPosition().y == 175)
			{
				// Set the position for text input
				userInputText.setPosition(650, 235);
				confirm = false;

				// Allow text input
				sf::Event textEvent;
				while (window.pollEvent(textEvent))
				{
					if (textEvent.type == sf::Event::TextEntered)
					{
						if (textEvent.text.unicode < 128)
						{
							if (textEvent.text.unicode == 8 && !userInput.isEmpty())  // Backspace
								userInput.erase(userInput.getSize() - 1);
							else
								userInput += textEvent.text.unicode;
						}
					}
					else if (textEvent.type == sf::Event::KeyPressed && textEvent.key.code == sf::Keyboard::Enter)
					{
						// Save the entered text and move to the next state
						// You can store or display the userInput as needed
						menu_state = new_worker_check;
						break;
					}
				}
			}
			if (menu_state == new_worker_type)
				if (confirm && select_ui_1_sprite.getPosition().y == 175)
				{
					select_ui_1_sprite.setPosition(650, 235);
					confirm = false;
				}
				else if (confirm && select_ui_1_sprite.getPosition().y == 235)
				{
					check_mark_sprite.setPosition(555, 395);
					confirm = false;
					menu_state = new_worker_check;
				}
			else if (menu_state == new_worker_type_1)
			{
				if (confirm && select_ui_1_sprite.getPosition().y == 535)
				{
					check_mark_1_sprite.setPosition(555, 660);
					confirm = false;
					menu_state = new_worker_check_1;
				}
			}
			if (moveup)
			{
				// Handle moving up  
				
				 if (menu_state == new_worker_type)
				{
					if (select_ui_1_sprite.getPosition().y <= 235)
						select_ui_1_sprite.move(0, -60);
				    if (select_ui_1_sprite.getPosition().y < 175)
					{
						check_mark_1_sprite.setPosition(555, 720);
						menu_state = new_worker_check_1;
					}

				}
				else if (menu_state == new_worker_check)
				{
					if (check_mark_sprite.getPosition().y <= 535)
						check_mark_sprite.move(0, -40);
					if (check_mark_sprite.getPosition().y < 395)
					{
						select_ui_1_sprite.setPosition(650, 235);
						menu_state = new_worker_type;
					}
				}
				else if (menu_state == new_worker_type_1)
				{
					if (select_ui_1_sprite.getPosition().y >= 535)
						select_ui_1_sprite.move(0, -60);
					if (select_ui_1_sprite.getPosition().y < 535)
					{
						check_mark_sprite.setPosition(555, 515);
						menu_state = new_worker_check;
					}
				}
				else if (menu_state == new_worker_check_1)
				{
					if (check_mark_1_sprite.getPosition().y <= 720)
						check_mark_1_sprite.move(0, -30);
					if (check_mark_1_sprite.getPosition().y < 660)
					{
						select_ui_1_sprite.setPosition(650, 535);
						menu_state = new_worker_type_1;
					}
				}
			}
			else if (movedown)
			{
				if (menu_state == new_worker_type) // name and surname (add new worker)
				{
					if (select_ui_1_sprite.getPosition().y >= 175)
						select_ui_1_sprite.move(0, +60);
				    if (select_ui_1_sprite.getPosition().y > 235)
					{
						check_mark_sprite.setPosition(555, 395);
						menu_state = new_worker_check;
					}
				}
				else if (menu_state == new_worker_check) // worker position (add new worker)
				{
					if (check_mark_sprite.getPosition().y >= 395)
						check_mark_sprite.move(0, +40);
					if (check_mark_sprite.getPosition().y >= 535)
					{
						select_ui_1_sprite.setPosition(650, 535);
						menu_state = new_worker_type_1;
					}
				}
				else if (menu_state == new_worker_type_1) // contract date (add new worker)
				{
					if (select_ui_1_sprite.getPosition().y >= 535)
						select_ui_1_sprite.move(0, +60);
					if (select_ui_1_sprite.getPosition().y > 535)
					{
						check_mark_1_sprite.setPosition(555, 660);
						menu_state = new_worker_check_1;
					}
				}
				else if (menu_state == new_worker_check_1) // contract length (add new worker)
				{
					if (check_mark_1_sprite.getPosition().y >= 660)
						check_mark_1_sprite.move(0, +30);
					if (check_mark_1_sprite.getPosition().y > 720)
					{
						select_ui_1_sprite.setPosition(650, 175);
						menu_state = new_worker_type;
					}
				}
			}
		}
		window.clear();
		switch (menu_state)
		{
		case new_worker_type: // Name 
			confirm = false;
			window.clear();
			window.draw(add_new_worker_sprite);
			window.draw(select_ui_1_sprite);
			break;
		case new_worker_check:
			confirm = false;
			window.draw(add_new_worker_sprite);
			window.draw(check_mark_sprite);
			break;
		case new_worker_type_1:
			confirm = false;
			window.draw(add_new_worker_sprite);
			window.draw(select_ui_1_sprite);
			break;
		case new_worker_check_1:
			confirm = false;
			window.draw(add_new_worker_sprite);
			window.draw(check_mark_1_sprite);
			break;
		}
		window.display();
	}
	return 0;

}