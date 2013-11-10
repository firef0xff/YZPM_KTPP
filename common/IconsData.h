

#ifndef IconsDataH
#define IconsDataH
#include <Controls.hpp>
#include "collation.h"
#include "vector.h"

class IconsData
	{
	public:
	IconsData(TComponent* Owner);
	~IconsData(void);
	void LoadCollation(int inbase, int InList, bool Accept, int type);  	
	int GetInList(int inbase, bool Accept, int type);                       
	TImageList * GetImgList (void)const {return IMGList;}
	TImageList * GetStateList (void)const {return StateList;}
	bool isEmpty;   												
	IconsData & operator = (const IconsData &r);
	private:
	TImageList *IMGList;
	TImageList *StateList;
	vector <collation> mass;       									
	};
#endif
