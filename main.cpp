#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>

class ShapeData
{
public:
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f dimensions;
	float radius;
	std::string kind;

	ShapeData(sf::Vector2f p, sf::Vector2f v, sf::Vector2f d) :
		position(p),
		velocity(v),
		dimensions(d),
		kind("Rectangle"),
		radius(0)
	{
	}

	ShapeData(sf::Vector2f p, sf::Vector2f v, float cr) :
		position(p),
		velocity(v),
		radius(cr),
		kind("Circle")
	{
	}

};
class CustomShape 
{
public:
	float window_w, window_h;
	std::string font_src;
	int font_size, font_cr, font_cg, font_cb;
	std::vector<std::shared_ptr<sf::Shape>> shapes;
	std::vector<std::shared_ptr<sf::Text>> texts;
	std::vector<ShapeData> shapeData;
	sf::Font font;

	void loadFile(std::string path) {
		std::ifstream fin(path);
		std::string temp;
		while (fin >> temp) {
			if (temp == "Window") {
				fin >> window_w >> window_h;
				std::cout << "Window \t" << window_w << ", " << window_h << "\n";
			}
			if (temp == "Font") {
				fin >> font_src >> font_size >> font_cr >> font_cg >> font_cb;
				std::cout << "Font \t" << font_src << "\t" << font_size << "\t" << font_cr << "," << font_cg << "," << font_cb << "\n";
				
				// attempt to load the font from a file
				if (!font.loadFromFile(font_src))
				{
					// if we can't load the font, print an error to the error console and exit
					std::cerr << "Could not load font!\n";
					exit(-1);
				}
			}
			if (temp == "Circle")
			{
				std::string cn;
				float cx, cy, vx, vy, cr;
				int c_r, c_g, c_b;
				fin >> cn >> cx >> cy >> vx >> vy >> c_r >> c_g >> c_b >> cr;
				std::cout << "Circle name " << cn << "\t\tcx, cy " << cx << ", " << cy
					<< "\t\tvx, vy " << vx << ", " << vy
					<< "\t\tR,G,B " << c_r << ", " << c_g << ", " << c_b << "\n";
				addShape(cn, cr, c_r, c_g, c_b, sf::Vector2f(cx, cy), sf::Vector2f(vx, vy));
			}

			if (temp == "Rectangle")
			{
				std::string rn;
				float rx, ry, vrx, vry, rw, rh;
				int r_r, r_g, r_b;
				fin >> rn >> rx >> ry >> vrx >> vry >> r_r >> r_g >> r_b >> rw >> rh;
				std::cout << "Rectangle name " << rn << "\t\trx, ry " << rx << ", " << ry
					<< "\t\tvrx, vry " << vrx << ", " << vry
					<< "\t\tR,G,B " << r_r << ", " << r_g << ", " << r_b << "\n";
				addShape(rn, sf::Vector2f(rw, rh), r_r, r_g, r_b, sf::Vector2f(rx, ry), sf::Vector2f(vrx, vry));
			}
		}
	}

	void addShape(std::string &shapeName, float cr, float c_r, float c_g, float c_b, sf::Vector2f position, sf::Vector2f velocity) {
		std::shared_ptr<sf::Shape> _circle = std::make_shared<sf::CircleShape>(cr);
		std::shared_ptr<sf::Text> _text = std::make_shared<sf::Text>(shapeName, font, font_size);
		_text -> setFillColor(sf::Color(font_cr, font_cg, font_cb));
		_text->setPosition(position.x + cr - (_text->getGlobalBounds().width / 2), position.y + cr - (_text->getGlobalBounds().height / 2));
		_circle -> setFillColor(sf::Color(c_r, c_g, c_b));
		_circle -> setPosition(position);
		shapes.push_back(_circle);
		shapeData.push_back(ShapeData(position, velocity, cr));
		texts.push_back(_text);
	}

	void addShape(std::string &shapeName, sf::Vector2f dimensions, float r_r, float r_g, float r_b, sf::Vector2f position, sf::Vector2f velocity) {
		std::shared_ptr<sf::Shape> _rectangle = std::make_shared<sf::RectangleShape>(dimensions);
		std::shared_ptr<sf::Text> _text = std::make_shared<sf::Text>(shapeName, font, font_size);
		_text -> setFillColor(sf::Color(font_cr, font_cg, font_cb));
		_text->setPosition(position.x + (dimensions.x / 2) - (_text->getGlobalBounds().width / 2), position.y + (dimensions.y / 2) - (_text->getGlobalBounds().height / 2));
		_rectangle -> setFillColor(sf::Color(r_r, r_g, r_b));
		_rectangle -> setPosition(position);
		shapes.push_back(_rectangle);
		shapeData.push_back(ShapeData(position, velocity, dimensions));
		texts.push_back(_text);
	}

};

int main(int argc, char* argv[])
{
	CustomShape cs = CustomShape();
	cs.loadFile("config.txt");

	sf::RenderWindow window(sf::VideoMode(cs.window_w, cs.window_h), "SFML works!");
	window.setFramerateLimit(60);

	// main loop - continues for each frame while window is open
	while (window.isOpen())
	{
		// Event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			// this event triggers when the window is closed
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
		}
		
		window.clear();			// clear the window of anything previously drawn

		for (size_t i = 0; i < cs.shapes.size(); i++)
		{
			std::shared_ptr<sf::Text> text = cs.texts[i];
			std::shared_ptr<sf::Shape> shape = cs.shapes[i];
			sf::Vector2f velocity = cs.shapeData[i].velocity;
			// std::cout << "New location (x,y)" << i << " \t" << shape->getPosition().x << ", " << shape->getPosition().y << "\n";
			float x = shape->getPosition().x + velocity.x;
			float y = shape->getPosition().y + velocity.y;
			float tx = text->getPosition().x + velocity.x;
			float ty = text->getPosition().y + velocity.y;
			if (x <= 0) 
			{
				cs.shapeData[i].velocity = sf::Vector2f(velocity.x * -1.0f, velocity.y);
			}
			if (y <= 0)
			{
				cs.shapeData[i].velocity = sf::Vector2f(velocity.x, velocity.y * -1.0f);
			}
			if (cs.shapeData[i].kind == "Circle") 
			{
				if (x + (2 * cs.shapeData[i].radius) >= cs.window_w)
				{
					cs.shapeData[i].velocity = sf::Vector2f(velocity.x * -1.0f, velocity.y);
				}
				if (y + (2 * cs.shapeData[i].radius) >= cs.window_h)
				{
					cs.shapeData[i].velocity = sf::Vector2f(velocity.x, velocity.y * -1.0f);
				}

			}
			if (cs.shapeData[i].kind == "Rectangle")
			{
				if (x + cs.shapeData[i].dimensions.x >= cs.window_w)
				{
					cs.shapeData[i].velocity = sf::Vector2f(velocity.x * -1.0f, velocity.y);
				}
				if (y + cs.shapeData[i].dimensions.y >= cs.window_h)
				{
					cs.shapeData[i].velocity = sf::Vector2f(velocity.x, velocity.y * -1.0f);
				}

			}
			shape -> setPosition(x, y);
			text  -> setPosition(tx, ty);
			// std::cout << "velocity (x,y)" << i << " \t" << velocity.x << ", " << velocity.y << "\n";
			window.draw(*shape);
			window.draw(*text);
		}

		window.display();		// call the window display function

	}
	return 0;

}