#include "Sprite.h"
#include <filesystem>



Sprite::Sprite(const std::string& pathFile, const Point2f& leftBottomPos) :
	m_Position	{ leftBottomPos },
	m_uTexture	{ std::make_unique<Texture>(pathFile) },
	m_uHitbox	{ std::make_unique<Rectf>(leftBottomPos.x, leftBottomPos.y, m_uTexture->GetWidth(), m_uTexture->GetHeight()) }
{
	std::cout<< "Created Sprite" << "\n";


	if (!m_uTexture->IsCreationOk())
		std::abort();

} 



Sprite::~Sprite()
{
	std::cout<< "Deleting Sprite" << "\n";
}



void Sprite::Draw() const
{
#if DEBUG_MESSAGE
	std::cout<< "Drawing Sprite" << "\n";
#endif

	m_uTexture->Draw();
	
	m_uHitbox->left		= m_Position.x;
	m_uHitbox->bottom	= m_Position.y;

}
 
 

void Sprite::Update(float elapsedSec)
{
	// nothing here
}
 


Rectf Sprite::GetHitBox() const
{
	
	if (m_uHitbox)
		return *m_uHitbox;
	else
		return Rectf();

}

//void Sprite::GotBridge(std::shared_ptr<bool> tester)
//{
//	m_test = tester;
//}

//std::shared_ptr<Rectf> Sprite::GetHitBoxtest()
//{
//	return m_uHitbox;
//}


