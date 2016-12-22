#include "Entity.h"

Entity::Entity() : m_array(sf::Quads, 4), m_size(10, 10)
{

	m_array[0].position = sf::Vector2f(0, 0);
	m_array[1].position = sf::Vector2f(m_size.x, 0);
	m_array[2].position = sf::Vector2f(m_size.x, m_size.y);
	m_array[3].position = sf::Vector2f(0, m_size.y);

	m_tex = new sf::Texture();
	if (!m_tex->loadFromFile("Ressources/textures/1.png"))
		cerr << "Error loading image : Ressources/textures/1.png" << endl;

	m_array[0].texCoords = sf::Vector2f(0, 0);
	m_array[1].texCoords = sf::Vector2f(m_tex->getSize().x, 0);
	m_array[2].texCoords = sf::Vector2f(m_tex->getSize().x, m_tex->getSize().y);
	m_array[3].texCoords = sf::Vector2f(0, m_tex->getSize().y);

	m_hasShaders = false;
}

Entity::Entity(sf::Vector2f pos, sf::Vector2f size, string tex, string vert_shader, string frag_shader) : m_array(sf::Quads, 4), m_size(size), m_texFile(tex), m_shader()
{
	m_array[0].position = pos;
	m_array[1].position = sf::Vector2f(pos.x + m_size.x, pos.y);
	m_array[2].position = sf::Vector2f(pos.x + m_size.x, pos.y + m_size.y);
	m_array[3].position = sf::Vector2f(pos.x, pos.y + m_size.y);

	m_tex = new sf::Texture();
	if (!m_tex->loadFromFile(m_texFile))
		cerr << "Error loading image : " + m_texFile << endl;

	m_array[0].texCoords = sf::Vector2f(0, 0);
	m_array[1].texCoords = sf::Vector2f(m_tex->getSize().x, 0);
	m_array[2].texCoords = sf::Vector2f(m_tex->getSize().x, m_tex->getSize().y);
	m_array[3].texCoords = sf::Vector2f(0, m_tex->getSize().y);

	if (!m_shader.loadFromFile(vert_shader, frag_shader))
	{
		cerr << "Error loading vertex shader : " + vert_shader << endl;
		cerr << "Error loading fragment shader : " + frag_shader << endl;
	}

	m_hasShaders = true;
}

Entity::Entity(sf::Vector2f pos, sf::Vector2f size, string tex) : m_array(sf::Quads, 4), m_size(size), m_texFile(tex), m_shader()
{
	m_array[0].position = pos;
	m_array[1].position = sf::Vector2f(pos.x + m_size.x, pos.y);
	m_array[2].position = sf::Vector2f(pos.x + m_size.x, pos.y + m_size.y);
	m_array[3].position = sf::Vector2f(pos.x, pos.y + m_size.y);

	m_tex = new sf::Texture();
	if (!m_tex->loadFromFile(m_texFile))
		cerr << "Error loading image : " + m_texFile << endl;

	m_array[0].texCoords = sf::Vector2f(0, 0);
	m_array[1].texCoords = sf::Vector2f(m_tex->getSize().x, 0);
	m_array[2].texCoords = sf::Vector2f(m_tex->getSize().x, m_tex->getSize().y);
	m_array[3].texCoords = sf::Vector2f(0, m_tex->getSize().y);

	m_hasShaders = false;
}

void Entity::move(sf::Vector2f pos)
{
	m_array[0].position += pos;
	m_array[1].position += pos;
	m_array[2].position += pos;
	m_array[3].position += pos;
}

void Entity::setSize(sf::Vector2f size)
{
	m_size = size;

	m_array[1].position = sf::Vector2f(m_array[0].position.x + m_size.x, m_array[0].position.y);
	m_array[2].position = sf::Vector2f(m_array[0].position.x + m_size.x, m_array[0].position.y + m_size.y);
	m_array[3].position = sf::Vector2f(m_array[0].position.x, m_array[0].position.y + m_size.y);
}

void Entity::setShaders(string vert_shader, string frag_shader)
{
	if (!m_shader.loadFromFile(vert_shader, frag_shader))
	{
		cerr << "Error loading vertex shader : " + vert_shader << endl;
		cerr << "Error loading fragment shader : " + frag_shader << endl;
	}

	m_hasShaders = true;
}

void Entity::setTexture(string tex)
{
	m_tex = new sf::Texture();
	if (!m_tex->loadFromFile(tex))
		cerr << "Error loading image : " + tex << endl;

	m_array[0].texCoords = sf::Vector2f(0, 0);
	m_array[1].texCoords = sf::Vector2f(m_tex->getSize().x, 0);
	m_array[2].texCoords = sf::Vector2f(m_tex->getSize().x, m_tex->getSize().y);
	m_array[3].texCoords = sf::Vector2f(0, m_tex->getSize().y);
}

void Entity::render(sf::RenderWindow *window)
{

	sf::RenderStates states;

	if (m_hasShaders)
		states.shader = &m_shader;
	states.texture = m_tex;
	states.blendMode = sf::BlendAlpha;

	window->draw(m_array, states);
}

sf::Vector2f Entity::rotate(float angle)
{
	sf::Transform rotation;
	rotation.rotate(angle, m_array[0].position.x + m_size.x / 2, m_array[0].position.y + m_size.y / 2);

	int i(0);
	for (i = 0; i < 4; i++)
	{
		m_array[i].position = rotation.transformPoint(m_array[i].position);
	}

	return m_array[0].position;
}

sf::Vector2f Entity::rotate(float angle, sf::Vector2f center)
{
	sf::Transform rotation;
	rotation.rotate(angle, center.x, center.y);

	int i(0);
	for (i = 0; i < 4; i++)
	{
		m_array[i].position = rotation.transformPoint(m_array[i].position);
	}

	return m_array[0].position;

}

void Entity::flip()
{
	sf::Vector2f temp(0, 0);

	temp = m_array[0].texCoords;
	m_array[0].texCoords = m_array[2].texCoords;
	m_array[2].texCoords = temp;

	temp = m_array[3].texCoords;
	m_array[3].texCoords = m_array[1].texCoords;
	m_array[1].texCoords = temp;
}

sf::Shader* Entity::getShader()
{
	return &m_shader;
}

Entity::~Entity()
{
}