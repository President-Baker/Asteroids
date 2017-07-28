#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
	float Dx;
	float Dy;

public:
	Velocity() : Dx(0.0), Dy(0.0)
	{}

	Velocity(float Dx, float Dy)
	{
		this->Dx = Dx;
		this->Dy = Dy;
	}

	float getDx(); 

	float getDy(); 

	void setDx(float Dx); 

	void setDy(float Dy); 
};



#endif /* velocity_h */
