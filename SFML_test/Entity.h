#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Entity
{
public:
	Entity();
	Entity(sf::Vector2f pos, sf::Vector2f size, string tex, string vert_shader, string frag_shader);
	Entity(sf::Vector2f pos, sf::Vector2f size, string tex);
	void move(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
	void setShaders(string vert_shader, string frag_shader);
	void setTexture(string tex);
	void render(sf::RenderWindow *window);
	sf::Vector2f rotate(float angle);
	sf::Vector2f rotate(float angle, sf::Vector2f center);
	void flip();
	sf::Shader *getShader();
	~Entity();

private:
	sf::Vector2f m_size;
	sf::VertexArray m_array;
	sf::Texture *m_tex;
	string m_texFile;
	sf::Shader m_shader;
	bool m_hasShaders;
};