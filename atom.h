
class   p3
{
public:
	double x,y,z;
	p3 (double _x=0., double _y=0., double _z=0.)
	{
		this ->x=_x;
		this ->y=_y;
		this ->z=_z;
	}
	~p3 ()
	{
    }
	p3 operator+ (p3 _p3)
	{
		p3 c(x + _p3.x, y + _p3.y, z + _p3.z);
		return c;
	}
	p3 operator- (p3 _p3)
	{
		p3 c(x - _p3.x, y - _p3.y, z - _p3.z);
		return c;
	}
	p3 operator* (p3 _p3)
	{
		p3 c(x * _p3.x, y * _p3.y, z * _p3.z);
		return c;
	}
	p3 operator* (double a)
	{
		p3 c(x*a,y*a,z*a);
		return c;
	}
	p3 operator/ (double a)
	{
		p3 c(x/a,y/a,z/a);
		return c;
	}
	void rotate(double fi){
		double _x = this->x;
		double _y = this->y;
		this->x = _x*cos(fi) - _y*sin(fi);
		this->y = _x*sin(fi) + _y*cos(fi);
	}
};







void drawatom(p3 v){
	glTranslated(v.x, v.y, v.z);
	glutSolidSphere(3, 7.0 ,7.0);
	glTranslated(-v.x, -v.y, -v.z);
}

double lenght(p3 p){
	return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}