#pragma once
#include "Model.h" 
#include "Transform.h" 
#include <memory> 

class Actor {
public: 
	Actor(const Transform& transform, std:: shared_ptr<Model> model): m_transform{transform}, m_model{model}{} 

	Transform& GetTransform() { return m_transform; } 
	const Transform& GetTransform() const { return m_transform; }

	void Draw(class Framebuffer& framebuffer, const class Camera& camera); 

	void SetColor(color_t color) { m_model->SetColor(color); }

private:
	Transform m_transform; 
	std::shared_ptr<Model> m_model;
};
 

//wooooAAAOOOWWwww pain thte town blue, riots all around you

//its only been like 3 hours since i seen my bf but i miss him
//i wanna be in his bed asleep
//30 more minutes in this class and then i get to get out of here
//im so exhausted i wanna go home 
//remember meeee
//i love arcane songs
//theyre so swaggy
//i miss my firelight
//my burn hurts so much right now
//its super sensitive for no reason
//im so so exhausted 
//i feel like i can fall asleep right here and rihgt now
//its hard to keep my eyes open
//and my muscle's hurt so so much 
//i want my bf to give me kisses again 
//its only been 10 minutes, i still have 20 more minutes in this class
//imma burn this classroom down i need to get out of here i have zero stimulation being here
//i feel like dropping out, i dont feel proud or achieved to finish projects, i just feel exhausted
//12 more minutes
//i hate it here
//20 20 20 20 visionnn 
//the longer this class goes on the more angry i feel the more i need to burn this place down  
//9 more minutes
//i just need to survice 9 more minutes
//flower boy album goes crazy rn 
//i wanna be held by jaxen, i wanna wake up and turn on my side and have him slink his arms around me and give my shoulder kisses
//thats when i feel the most at peace, it could be boiling hot we could be sweating, the world could be ending around us, and i feel the most peace around him 
//7 more minutes 
//i cant tell if i need sleep, food, affection, or a mix of all 3 
//time moves by so slowly i  wanna leave 
//3 more minutes
//then i can see my friends
//and goof off with my boyfriend 
//and be relaxed, i need it so badly
//i feel so behind even though looking at it, im fine 
//IM FREEE 
