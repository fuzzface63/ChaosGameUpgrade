// Include important C++ libraries here 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace" // 
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game 
	RenderWindow window(vm, "Square Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	// Load font ONCE before the loop starts
	Font font;
	if (!font.loadFromFile("ARIAL.TTF")) {
		cout << "Error loading font!" << endl;
	}

	Text instructions;
	instructions.setFont(font);
	instructions.setCharacterSize(24);
	instructions.setFillColor(Color::White);
	instructions.setPosition(100, 10);
	instructions.setString("1. Click 5 times to set Vertices\n2. Click a 6th time to start the Chaos");

	srand(time(0));

	int lastVertexIndex = -1;
	while (window.isOpen())
	{
		
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 5)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			for (int i = 0; i < 100; i++)
			{
				// pick a point 
				int myVertexIndex = rand() % vertices.size();  
				// can't be equal to previous
				// This constraint prevents "clouds"
				// It checks if the new vertex is the same OR a neighbor of the last one
				while (myVertexIndex == lastVertexIndex ||
					myVertexIndex == (lastVertexIndex + 1) % 5 ||
					myVertexIndex == (lastVertexIndex + 4) % 5)
				{
					myVertexIndex = rand() % vertices.size();
				}
				lastVertexIndex = myVertexIndex;

				// get last point
				Vector2f currPoint = points.back(); // last click info
				Vector2f randPoint = vertices[myVertexIndex]; // random one of 4 points

				Vector2f nearPoint;
				nearPoint.x = randPoint.x;
				nearPoint.y = randPoint.y;
				
				
				
				Vector2f nextPlace, nextPlace2;
				nextPlace.x = (2.0f * currPoint.x + randPoint.x) / 3.0f; // average of x make it float
				nextPlace.y = (2.0f * currPoint.y + randPoint.y) / 3.0f; // average of y make it float
					 
				// push it back to the vector
				points.push_back(nextPlace);
					 
				
				
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		// Draw Instructions
		window.draw(instructions); 
		
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(2,2));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		///TODO:  Draw points

		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape myPoint(Vector2f(1,1)); 
			myPoint.setPosition(points[i]);
			myPoint.setFillColor(Color::Blue);
			window.draw(myPoint);
		}
		window.display();
	}
}
