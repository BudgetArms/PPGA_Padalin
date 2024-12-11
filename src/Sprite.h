#pragma once

//#include "Texture.h"

class Sprite
{

public:

	Sprite(const std::string& pathFile, const Point2f& leftBottomPos = Point2f{ 0, 0 });
	
	Sprite(Sprite&)				= delete; // Copy Constructor
	Sprite(Sprite&&)			= delete; // Move Constructor
	Sprite operator&=(Sprite&)	= delete; // Copy Assignment
	Sprite operator&=(Sprite&&)	= delete; // Move Assignment

	virtual ~Sprite();

	virtual void Draw() const;
	virtual void Update(float elapsedSec);

	Rectf GetHitBox() const;

	Point2f		m_Position;

private:


protected:


	//std::unique_ptr<Texture>	m_uTexture;
	std::unique_ptr<Rectf>		m_uHitbox;




};

