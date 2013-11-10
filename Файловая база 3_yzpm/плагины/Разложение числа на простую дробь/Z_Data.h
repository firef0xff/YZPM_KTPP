//---------------------------------------------------------------------------

#ifndef Z_DataH
#define Z_DataH
class Z_Data
{
public:
	Z_Data(int _z1,int _z2,int _z3,int _z4);
	Z_Data(const Z_Data &);
	~Z_Data(void);
	int Z1(void)const{return z1;}
	int Z2(void)const{return z2;}
	int Z3(void)const{return z3;}
	int Z4(void)const{return z4;}
	int U(void)const {return u;}
	Z_Data& operator =	(const Z_Data&);
	bool 	operator ==	(const Z_Data&);
	bool 	operator !=	(const Z_Data&);
private:
int z1;
int z2;
int z3;
int z4;
double u;
};
#endif
