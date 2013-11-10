//---------------------------------------------------------------------------

#ifndef Settings_wndH
#define Settings_wndH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>

#include <ImgList.hpp>
#include "SQL.h"
#define USERIDCOL 1
#define GROUPIDCOL 1
#define CONDIDCOL 1
#define GTUGROUPIDCOL 1
#define GTSGROUPIDCOL 1
#define PSGROUPIDCOL 2
//---------------------------------------------------------------------------
class TSettings : public TForm
{
__published:    // IDE-managed Components
    TPageControl *pcMain;
    TTabSheet *tsUsers;
    TTabSheet *tsLists;
    TPanel *Panel2;
    TPanel *Panel1;
    TStringGrid *sgUsers;
    TPopupActionBar *pabUsers;
    TMenuItem *UserAdd;
    TMenuItem *UserUpdate;
    TMenuItem *UserDel;
    TPopupActionBar *pabGroups;
    TMenuItem *AddGroup;
    TMenuItem *GroupDel;
    TPopupActionBar *pabRights;
    TMenuItem *AddRight;
    TMenuItem *DeleteRight;
    TMenuItem *UserInformation;
    TImageList *images;
    TImageList *ImageList1;
    TStringGrid *sgGroups;
    TPanel *Panel3;
    TStringGrid *sgRights;
    TPanel *Panel4;
    TPanel *Panel5;
    TPanel *Panel6;
    TPanel *Panel7;
    TStringGrid *sgGroupRights;
    TPanel *Panel8;
    TMenuItem *GroupEdit;
    TTabSheet *tsEquipment;
    TTabSheet *tsGroupsAndStates;
    TTabSheet *TabSheet3;
    TPanel *Panel9;
    TPanel *Panel10;
    TStringGrid *sgStates;
    TPanel *Panel11;
    TPageControl *pcStatesSettings;
    TTabSheet *tsGTU;
    TTabSheet *tsGTS;
    TTabSheet *tsPS;
    TStringGrid *sgGTU;
    TStringGrid *sgGTS;
    TStringGrid *sgPS;
    TPopupActionBar *pabGTUS;
    TMenuItem *miGTUSAdd;
    TMenuItem *miGTUSDel;
    TPopupActionBar *pabPS;
    TMenuItem *miNextStateAdd;
    TMenuItem *miNextStateEdit;
    TMenuItem *miNextStateDel;
    void __fastcall sgDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
    void __fastcall UserAddClick(TObject *Sender);
    void __fastcall UserUpdateClick(TObject *Sender);
    void __fastcall sgUsersSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
    void __fastcall UserDelClick(TObject *Sender);
    void __fastcall UserInformationClick(TObject *Sender);
    void __fastcall AddGroupClick(TObject *Sender);
    void __fastcall GroupDelClick(TObject *Sender);
    void __fastcall pcMainChange(TObject *Sender);
    void __fastcall sgGroupsSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
    void __fastcall GroupEditClick(TObject *Sender);
    void __fastcall AddRightClick(TObject *Sender);
    void __fastcall DeleteRightClick(TObject *Sender);
    void __fastcall pcStatesSettingsChange(TObject *Sender);
    void __fastcall sgStatesSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
    void __fastcall miGTUSAddClick(TObject *Sender);
    void __fastcall miGTUSDelClick(TObject *Sender);
    void __fastcall miNextStateAddClick(TObject *Sender);
    void __fastcall miNextStateEditClick(TObject *Sender);
    void __fastcall miNextStateDelClick(TObject *Sender);



private:    // User declarations
    cSQL *DB;
    const int    &LUser;  //идентификатор пользователя
    bool     _UserADD,            //настройки безопасности
            _UserDel,
            _UserEdit,
            _GroupsEdit,
            _ChangePSWD;
    //вкладка настройки пользователей
    void     Get_Users        (void);//загрузка пользователей
    void    Get_Rights        (int Row);//отображение списка прав для пользователя
    //вкладка настройки групп
    void    Get_AllGroups   (void);//получение общего списка групп с правами
    void    Get_GroupsRights(int Row);//отображение списка прав для групп
    //вкладка настройки состояний
    void    Get_Conditions    (void);        //получение списка возможных состояний
    void    Get_UsedGroups    (int Row);  //получение списка групп использующих состояние
    void    Get_SetGroups    (int Row);  //получение списка групп устанавливающих состояние
    void    Get_NextConditions(int Row);//получение списка состояний следующих после данного
    //наполнение сетки
    void    Fill_Greed       (String sql,TStringGrid *sg,int offset=0);

public:        // User declarations
    __fastcall TSettings(TComponent* Owner,cSQL *db,const int&_LUser);
};
#endif
