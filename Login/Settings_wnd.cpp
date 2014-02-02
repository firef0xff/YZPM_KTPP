//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Settings_wnd.h"
#include "User_Data.h"
#include "Input_wnd.h"
#include "RightSelect.h"
#include "GTUSdialog.h"
#include "NextStateSelector.h"
#include "functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


__fastcall TSettings::TSettings(TComponent* Owner,cSQL *db,const int&_LUser): TForm(Owner),DB(db),LUser(_LUser)
{//закончена
    pcMain->OnChange(pcMain);
    _UserADD=false;
    _UserDel=false;
    _UserEdit=false;
    _GroupsEdit=false;
    _ChangePSWD=false;
    String sql="call administration.Get_Rights('"+String(LUser)+"')";
    TADOQuery *rez=DB->SendSQL(sql);
    if(rez&&rez->RecordCount)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            const String val=rez->FieldByName("progname")->Value;
            if (val=="UserADD")
            {
                _UserADD=true;
            }
            if (val=="UserDel")
            {
                _UserDel=true;
            }
            if (val=="UserEdit")
            {
                _UserEdit=true;
            }
            if (val=="GroupsEdit")
            {
                _GroupsEdit=true;
            }
            if (val=="ChangePSWD")
            {
                _ChangePSWD=true;
            }
        }
    }
    delete rez;
    UserAdd->Visible=_UserADD;
    UserUpdate->Visible=_UserEdit+_ChangePSWD;
    UserDel->Visible=_UserDel;
    if (_GroupsEdit)
    {
        sgGroups->PopupMenu=pabGroups;
        sgGroupRights->PopupMenu=pabRights;
        sgPS->PopupMenu=pabPS;
        sgGTS->PopupMenu=pabGTUS;
        sgGTU->PopupMenu=pabGTUS;
    }
    sgPS->Cells[0][0]="Название";
    sgPS->Cells[1][0]="Тип";
    ShowModal();
}
//функции
void     TSettings::Get_Users    (void)
{//закончена
    Fill_Greed("Select LogIn,LogID from administration.logins order by LogIn",sgUsers,1);
    AutoWidthSG(sgUsers);
    Get_Rights(sgUsers->Row);
}
void    TSettings::Get_Rights    (int Row)
{//закончена
    if (Row<sgUsers->RowCount)
    {//кинуть запрос по группе расшифровать
        String id=sgUsers->Cells[USERIDCOL][Row]==""?String(0):sgUsers->Cells[USERIDCOL][Row];
        String sql=    "call administration.Get_Rights("+id+")";
        Fill_Greed(sql,sgRights,0);
        AutoWidthSG(sgRights);
    }
}
void    TSettings::Get_AllGroups(void)
{//закончена
    Fill_Greed("Select GroupName,GroupID from administration.privileges order by GroupName",sgGroups,1);
    AutoWidthSG(sgGroups);
    Get_GroupsRights(sgGroups->Row);
}
void    TSettings::Get_GroupsRights    (int Row)
{//закончена
    if (Row<sgGroups->RowCount)
    {//кинуть запрос по группе расшифровать
        String id=sgGroups->Cells[GROUPIDCOL][Row]==""?String(0):sgGroups->Cells[GROUPIDCOL][Row];
        String sql=    "call administration.Get_GroupsRights('"+id+"')";
        Fill_Greed(sql,sgGroupRights,0);
        AutoWidthSG(sgGroupRights);
    }
}
//вкладка настройки состояний
void    TSettings::Get_Conditions    (void)
{//получение списка возможных состояний
//закончена
    Fill_Greed("Select name,idsost from administration.conditions order by idsost",sgStates,1);
    AutoWidthSG(sgStates);
    pcStatesSettingsChange(nullptr);
}
void    TSettings::Get_UsedGroups    (int Row)
{//получение списка групп использующих состояние
    //закончена
    String t=sgStates->Cells[CONDIDCOL][Row];
    if (t!="")
    {
        Fill_Greed( "SELECT b.GroupName,b.GroupID "
                    "FROM administration.gtucond a "
                    "join administration.privileges b on a.IdGroup=b.GroupID "
                    "where a.IdCond='"+t+"' "
                    "order by b.GroupName; ",sgGTU,1);
        AutoWidthSG(sgGTU);
    }
}
void    TSettings::Get_SetGroups    (int Row)
{//получение списка групп устанавливающих состояние
    //закончена
    String t=sgStates->Cells[CONDIDCOL][Row];
    if (t!="")
    {
        Fill_Greed( "SELECT b.GroupName,b.GroupID "
                    "FROM administration.gtscond a "
                    "join administration.privileges b on a.IdGroup=b.GroupID "
                    "where a.IdCond='"+t+"' "
                    "order by b.GroupName; ",sgGTS,1);
        AutoWidthSG(sgGTS);
    }
}
void    TSettings::Get_NextConditions(int Row)
{//получение списка состояний следующих после данного
    //разработка
    String t=sgStates->Cells[CONDIDCOL][Row];
    if (t!="")
    {
        Fill_Greed( "SELECT b.`name`,if (a.type is not null,if(a.type='basic','Базовое направление','Ручной перевод'),'')as type,b.idsost "
                    "FROM administration.treeconds a "
                    "join administration.conditions b on a.IdNextCond=b.idsost "
                    "where a.IdCond='"+t+"' "
                    "order by a.type desc, b.name; ",sgPS,1);
        AutoWidthSG(sgPS);
    }
}
//обработчики сетки
void __fastcall TSettings::sgDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{//закончена
//обработка выделения
    TStringGrid *sg=(TStringGrid *)Sender;
    // выделенные поля
    if(ACol>=sg->Selection.Left&&ACol<=
        sg->Selection.Right&&ARow>=sg->Selection.Top&&ARow<=
        sg->Selection.Bottom) // выделение
    {
        sg->Canvas->Brush->Color=sg->Color; // clMenu;
        sg->Canvas->FillRect(Rect);
        sg->Canvas->Font->Color=clBlack;
        sg->Canvas->TextOut(Rect.left+2, Rect.top+1,sg->Cells[ACol][ARow]);
    }
}
//обработка триггеров
void __fastcall TSettings::pcMainChange(TObject *Sender)
{//закончена
    switch (pcMain->ActivePage->Tag)
    {
        case 0:{Get_Users();break;}
        case 1:{Get_AllGroups();break;}
        case 2:{Get_Conditions();break;}
        default:return;
    }
}
void __fastcall TSettings::pcStatesSettingsChange(TObject *Sender)
{//закончена
    switch (pcStatesSettings->ActivePage->Tag)
    {
        case 0:{Get_UsedGroups(sgStates->Row);break;}
        case 1:{Get_SetGroups(sgStates->Row);break;}
        case 2:{Get_NextConditions(sgStates->Row);break;}
        default:return;
    }
}
void __fastcall TSettings::sgUsersSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{//закончена
    Get_Rights(ARow);
}
void __fastcall TSettings::sgGroupsSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{//закончена
    Get_GroupsRights(ARow);
}
void __fastcall TSettings::sgStatesSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{//закончена
    switch (pcStatesSettings->ActivePage->Tag)
    {
        case 0:{Get_UsedGroups(ARow);break;}
        case 1:{Get_SetGroups(ARow);break;}
        case 2:{Get_NextConditions(ARow);break;}
        default:return;
    }
}
//--обработка меню
void __fastcall TSettings::UserAddClick(TObject *Sender)
{//закончена
    TUserData *wnd=new TUserData(this,DB);
    if (wnd->ShowModal()==mrOk)
    {
        //проверка наличия логина в базе
        String msg="";
        TADOQuery *rez=DB->SendSQL("Select login from administration.logins where login='"+wnd->leLogin->Text.Trim()+"'");
        if (rez)
        {
            if (rez->RecordCount)
            {//уже есть в базе
                MessageBoxW(Handle,L"Пользователь уже есть в базе",L"Внимание!",MB_ICONWARNING|MB_OK);
            }else
            {
                //составление запроса
                String sql=    "insert into administration.logins (Login,Name,Family,Otch,Pass,Levelacss) "
                            "Values ('"+wnd->leLogin->Text.Trim()+"',"
                            "'"+wnd->leName->Text.Trim()+"',"
                            "'"+wnd->leFam->Text.Trim()+"',"
                            "'"+wnd->leOtch->Text.Trim()+"',"
                            "PASSWORD('"+wnd->lePass->Text.Trim()+"'),"
                            "'"+String(int(wnd->cbGroup->Items->Objects[wnd->cbGroup->ItemIndex]))+"') ";
                //добавление пользователя
                DB->SendCommand(sql);
            }
        }
        delete rez;
    }
    delete wnd;
    Get_Users();
}
void __fastcall TSettings::UserUpdateClick(TObject *Sender)
{//закончена
    if (sgUsers->RowCount&&(_UserEdit||_ChangePSWD&&sgUsers->Cells[USERIDCOL][sgUsers->Row]==String(LUser)))
    {
        //проверка наличия логина в базе
        TADOQuery *rez=DB->SendSQL("Select login,name,family,Otch,Levelacss from administration.logins where logID=\'"+sgUsers->Cells[USERIDCOL][sgUsers->Row]+"\'");
        if (rez)
        {
            if (rez->RecordCount)
            {//уже есть в базе
                TUserData *wnd=new TUserData(this,DB);
                wnd->leFam->Text=rez->FieldByName("family")->Value.IsNull()?UnicodeString():rez->FieldByName("family")->Value.operator UnicodeString();
                wnd->leName->Text=rez->FieldByName("name")->Value.IsNull()?UnicodeString():rez->FieldByName("name")->Value.operator UnicodeString();
                wnd->leLogin->Text=rez->FieldByName("login")->Value.IsNull()?UnicodeString():rez->FieldByName("login")->Value.operator UnicodeString();
                wnd->leOtch->Text=rez->FieldByName("Otch")->Value.IsNull()?UnicodeString():rez->FieldByName("Otch")->Value.operator UnicodeString();
                int id=rez->FieldByName("Levelacss")->Value.IsNull()?0:rez->FieldByName("Levelacss")->Value.operator int();
                wnd->cbGroup->ItemIndex=wnd->cbGroup->Items->IndexOfObject((TObject*)id);
                if (wnd->ShowModal()==mrOk)
                {

                    //составление запроса
                    String sql=    "update administration.logins set Login='"+wnd->leLogin->Text.Trim()+"',"
                                "Name='"+wnd->leName->Text.Trim()+"',"
                                "Family='"+wnd->leFam->Text.Trim()+"',"
                                "Otch='"+wnd->leOtch->Text.Trim()+"',"
                                "Pass=PASSWORD('"+wnd->lePass->Text.Trim()+"') ";
                                if (_UserEdit)
                                {
                                    sql+=",Levelacss='"+String(int(wnd->cbGroup->Items->Objects[wnd->cbGroup->ItemIndex]))+"' ";
                                }
                                sql+="where LogID='"+sgUsers->Cells[USERIDCOL][sgUsers->Row]+"'";

                    //обновление данных пользователя
                    DB->SendCommand(sql);
                }
                delete wnd;
            }else
            {//нет в базе
                MessageBoxW(Handle,L"Пользователя уже нет в базе",L"Внимание!",MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
    }
    Get_Users();
}
void __fastcall TSettings::UserDelClick(TObject *Sender)
{//закончена
    if (sgUsers->RowCount)
    {
        //проверка наличия записи
        String sql="SELECT a.LogID FROM administration.logins a ";
        sql+="Where a.LogID='"+sgUsers->Cells[USERIDCOL][sgUsers->Row]+"'";
        TADOQuery *rez=DB->SendSQL(sql);
        if (rez)
        {
            if (rez->RecordCount)
            {//есть запись
                //удаление записи
                String sql="delete from administration.logins where ";
                sql+="LogID='"+sgUsers->Cells[USERIDCOL][sgUsers->Row]+"'";

                DB->SendCommand(sql);
            }else
            {//нет записи
                MessageBoxW(Handle,L"Пользователь отсутствует",L"Внимание!",MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
    }
    Get_Users();
}
void __fastcall TSettings::UserInformationClick(TObject *Sender)
{//закончена
    if (sgUsers->RowCount)
    {
        //проверка наличия логина в базе
        TADOQuery *rez=DB->SendSQL("Select login,name,family,Otch,Levelacss from administration.logins where logID='"+sgUsers->Cells[USERIDCOL][sgUsers->Row]+"'");
        if (rez)
        {
            if (rez->RecordCount)
            {//уже есть в базе
                TUserData *wnd=new TUserData(this,DB);
                wnd->leFam->Text=rez->FieldByName("family")->Value.IsNull()?UnicodeString():rez->FieldByName("family")->Value.operator UnicodeString();
                wnd->leName->Text=rez->FieldByName("name")->Value.IsNull()?UnicodeString():rez->FieldByName("name")->Value.operator UnicodeString();
                wnd->leLogin->Text=rez->FieldByName("login")->Value.IsNull()?UnicodeString():rez->FieldByName("login")->Value.operator UnicodeString();
                wnd->leOtch->Text=rez->FieldByName("Otch")->Value.IsNull()?UnicodeString():rez->FieldByName("Otch")->Value.operator UnicodeString();
                int id=rez->FieldByName("Levelacss")->Value.IsNull()?0:rez->FieldByName("Levelacss")->Value.operator int();
                wnd->cbGroup->ItemIndex=wnd->cbGroup->Items->IndexOfObject((TObject*)id);
                wnd->lePass->Hide();
                wnd->leName->ReadOnly=true;
                wnd->leFam->ReadOnly=true;
                wnd->leLogin->ReadOnly=true;
                wnd->leOtch->ReadOnly=true;
                wnd->cbGroup->Enabled=false;
                wnd->ShowModal();
                delete wnd;
            }else
            {//нет в базе
                MessageBoxW(Handle,L"Пользователя уже нет в базе",L"Внимание!",MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
    }
    Get_Users();
}
//работа с группами
void __fastcall TSettings::AddGroupClick(TObject *Sender)
{//закончена
    //получить группу
    if (sgUsers->RowCount)
    {
        TnewItem *wnd=new TnewItem(this);
        if (wnd->ShowModal()==mrOk)
        {
            String     csql="select a.GroupID from administration.privileges a where a.GroupName='"+wnd->leItem->Text+"'", //запрос проверки наличия
                    isql="insert into administration.privileges (GroupName) values('"+wnd->leItem->Text+"') "; //команда вставки

            TADOQuery *rez=DB->SendSQL(csql);
            if (rez)
            {
                if (rez->RecordCount)
                {//есть запись
                    MessageBoxW(Handle,L"Такая группа уже существует",L"Внимание!",MB_ICONWARNING|MB_OK);
                }else
                {//нет записи
                    //добавление записи
                    DB->SendCommand(isql);
                }
            }
            delete rez;
            Get_AllGroups();
        }
        delete wnd;
    }
}
void __fastcall TSettings::GroupEditClick(TObject *Sender)
{ //закончена
    //получить группу
    if (sgUsers->RowCount)
    {
        String     sql="select a.GroupID,a.GroupName from administration.privileges a "
                    "where a.GroupID='"+sgGroups->Cells[GROUPIDCOL][sgGroups->Row]+"'"; //запрос проверки наличия
        TADOQuery *rez=DB->SendSQL(sql);
        if (rez)
        {
            if (rez->RecordCount)
            {//есть запись
                TnewItem *wnd=new TnewItem(this);
                wnd->leItem->Text=rez->FieldByName("GroupName")->Value;
                if (wnd->ShowModal()==mrOk)
                {
                    sql="update administration.privileges set GroupName='"+wnd->leItem->Text+"' "
                        "where GroupID='"+sgGroups->Cells[GROUPIDCOL][sgGroups->Row]+"' "; //команда вставки
                    DB->SendCommand(sql);
                    Get_AllGroups();
                }
                delete wnd;

            }else
            {//нет записи
                MessageBoxW(Handle,L"Такой группы не существует",L"Внимание!",MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
    }
}
void __fastcall TSettings::GroupDelClick(TObject *Sender)
{//закончена
    if (sgUsers->RowCount)
    {
        String     csql, //запрос проверки наличия
                dsql; //команда удаления
                csql="SELECT a.GroupID FROM administration.privileges a ";
                csql+="Where a.GroupID='"+sgGroups->Cells[GROUPIDCOL][sgGroups->Row]+"'";

                dsql="delete from administration.privileges where GroupID='"+sgGroups->Cells[GROUPIDCOL][sgGroups->Row]+"'";

        //проверка наличия записи
        TADOQuery *rez=DB->SendSQL(csql);
        if (rez)
        {
            if (rez->RecordCount)
            {//есть запись
                //удаление записи
                DB->SendCommand(dsql);
            }else
            {//нет записи
                MessageBoxW(Handle,L"Такой группы не существует",L"Внимание!",MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
        Get_AllGroups();
    }
}
//работа с разрешениями
void __fastcall TSettings::AddRightClick(TObject *Sender)
{//закончена
    //получить группу
    if (sgGroups->RowCount)
    {
        TfselRight *wnd=new TfselRight(this,DB,sgGroups->Cells[GROUPIDCOL][sgGroups->Row]);
        if (wnd->ShowModal()==mrOk)
        {
            String     csql, //запрос проверки наличия
                    isql; //команда вставки
            csql="select b.ID from administration.privilegesrights a "
                 "join administration.rights b on b.ID=a.RidhtID "
                 "where a.PrivilegeID="+sgGroups->Cells[GROUPIDCOL][sgGroups->Row]+" and b.name='"+wnd->cbRight->Text+"'";

            isql="insert into administration.privilegesrights (RidhtID,PrivilegeID) "
                 "select a.id,'"+sgGroups->Cells[GROUPIDCOL][sgGroups->Row]+"' from administration.rights a "
                 "where a.name='"+wnd->cbRight->Text+"'";

            //проверка наличия записи
            TADOQuery *rez=DB->SendSQL(csql);
            if (rez)
            {
                if (rez->RecordCount)
                {//есть запись
                    MessageBoxW(Handle,L"Право уже принадлежит этой группе",L"Внимание!",MB_ICONWARNING|MB_OK);
                }else
                {//нет записи
                    //добавление записи
                    DB->SendCommand(isql);
                }
            }
            delete rez;
            Get_GroupsRights(sgGroups->Row);
        }
        delete wnd;
    }
}
void __fastcall TSettings::DeleteRightClick(TObject *Sender)
{//закончена
    if (sgGroups->RowCount)
    {
        String     csql, //запрос проверки наличия
                dsql; //команда удаления
        csql="select b.ID from administration.privilegesrights a "
             "join administration.rights b on b.ID=a.RidhtID "
             "where a.PrivilegeID="+sgGroups->Cells[GROUPIDCOL][sgGroups->Row]+" "
             "and b.name='"+sgGroupRights->Cells[0][sgGroupRights->Row]+"'";
        dsql="delete from administration.privilegesrights where "
             "RidhtID in (select ID from administration.rights where Name='"+sgGroupRights->Cells[0][sgGroupRights->Row]+"') and "
             "PrivilegeID='"+sgGroups->Cells[GROUPIDCOL][sgGroups->Row]+"' ";

        //проверка наличия записи
        TADOQuery *rez=DB->SendSQL(csql);
        if (rez)
        {
            if (rez->RecordCount)
            {//есть запись
                //удаление записи
                DB->SendCommand(dsql);
            }else
            {//нет записи
                MessageBoxW(Handle,L"Право отсутствует в этой группе",L"Внимание!",MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
        Get_GroupsRights(sgGroups->Row);
    }
}
//работа с состояниями
void __fastcall TSettings::miGTUSAddClick(TObject *Sender)
{//добавить GTU/GTS
//закончена
    //выбор таблицы в зависимости от открытой вкладки
    String Table,idCond=sgStates->Cells[CONDIDCOL][sgStates->Row];
    if (idCond=="")
    {
        return;
    }
    switch (pcStatesSettings->ActivePage->Tag)
    {
        case 0:{Table="gtucond";break;}
        case 1:{Table="gtscond";break;}
        default:return;
    }
    TGTUSGroupSelector *wnd=new TGTUSGroupSelector(this,DB,Table,idCond);//окно выбора группы
    if (wnd->ShowModal()==mrOk)
    {
        String idGroup=String(wnd->ID);
        TADOQuery *rez=DB->SendSQL("Select IdCond,IdGroup from administration."+Table+" where IdCond="+idCond+" and IdGroup="+idGroup);//проверка наличия связки идентификаторов
        if (rez)
        {
            if (!rez->RecordCount)
            {//действие
                DB->SendCommand("insert into administration."+Table+" (IdCond,IdGroup) values('"+idCond+"','"+idGroup+"')");
                pcStatesSettingsChange(nullptr);
            }else
            {//исключение
                MessageBox(Handle,_T("Группа уже есть в списке"),_T("Внимание"),MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
    }
    delete wnd;
}
void __fastcall TSettings::miGTUSDelClick(TObject *Sender)
{//удалить GTU/GTS
//закончена
    //выбор таблицы в зависимости от открытой вкладки
    String Table,idCond=sgStates->Cells[CONDIDCOL][sgStates->Row],idGroup;
    if (idCond=="")
    {
        return;
    }
    switch (pcStatesSettings->ActivePage->Tag)
    {
        case 0:    {
                    Table="gtucond";
                    idGroup=sgGTU->Cells[GTUGROUPIDCOL][sgGTU->Row];
                    break;
                }
        case 1:    {
                    Table="gtscond";
                    idGroup=sgGTS->Cells[GTSGROUPIDCOL][sgGTS->Row];
                    break;
                }
        default:return;
    }
    TADOQuery *rez=DB->SendSQL("Select IdCond,IdGroup from administration."+Table+" where IdCond="+idCond+" and IdGroup="+idGroup);//проверка наличия связки идентификаторов
    if (rez)
    {
        if (rez->RecordCount)
        {//действие
            DB->SendCommand("delete from administration."+Table+" where IdCond='"+idCond+"' and IdGroup='"+idGroup+"'");
            pcStatesSettingsChange(nullptr);
        }else
        {//исключение
            MessageBox(Handle,_T("Группа отсутствует в списке"),_T("Внимание"),MB_ICONWARNING|MB_OK);
        }
    }
    delete rez;
}
void __fastcall TSettings::miNextStateAddClick(TObject *Sender)
{//Добавить след состоние
//закончена
    String idCond=sgStates->Cells[CONDIDCOL][sgStates->Row];
    TNext_State_Selector *wnd=new TNext_State_Selector(this,DB,idCond);
    if (wnd->ShowModal()==mrOk)
    {//окно выбора состояния и типа направления
        String nextSate(wnd->ID),nextType(wnd->type);
        TADOQuery *rez=DB->SendSQL("Select * from administration.treeconds a where a.IdCond="+idCond+" and a.IdNextCond="+nextSate);
        if (rez)//проверка наличия пары состояний
        {
            if (!rez->RecordCount)
            {//действие
                if (nextType=="basic")
                {//если выбрано базовое направление
                    DB->SendCommand("Update administration.treeconds a set type='optional' where a.IdCond="+idCond);
                }
                DB->SendCommand("Insert into administration.treeconds (IdCond,IdNextCond,type) values('"+idCond+"','"+nextSate+"','"+nextType+"')");
                pcStatesSettingsChange(nullptr);
            }else
            {//исключения
                MessageBox(Handle,_T("Состояние уже есть в списке"),_T("Внимание"),MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
    }
    delete wnd;
}
void __fastcall TSettings::miNextStateEditClick(TObject *Sender)
{//Редактировать след состоние
//разработка
    String idCond=sgStates->Cells[CONDIDCOL][sgStates->Row],idNext=sgPS->Cells[PSGROUPIDCOL][sgPS->Row];
    TNext_State_Selector *wnd=new TNext_State_Selector(this,DB,idCond,true);
    if (wnd->ShowModal()==mrOk)
    {//окно выбора состояния и типа направления
        String nextType(wnd->type);
        TADOQuery *rez=DB->SendSQL("Select * from administration.treeconds a where a.IdCond="+idCond+" and a.IdNextCond="+idNext);
        if (rez)//проверка наличия пары состояний
        {
            if (rez->RecordCount)
            {//действие
                if (nextType=="basic")
                {//если выбрано базовое направление
                    DB->SendCommand("Update administration.treeconds a set type='optional' where a.IdCond="+idCond);
                }
                DB->SendCommand("Update administration.treeconds a set type='"+nextType+"' where a.IdCond="+idCond+" and a.IdNextCond="+idNext);
                pcStatesSettingsChange(nullptr);
            }else
            {//исключения
                MessageBox(Handle,_T("Состояние отсутствует в списке"),_T("Внимание"),MB_ICONWARNING|MB_OK);
            }
        }
        delete rez;
    }
    delete wnd;
}
void __fastcall TSettings::miNextStateDelClick(TObject *Sender)
{//Удалить след состоние
//закончена
    String idCond=sgStates->Cells[CONDIDCOL][sgStates->Row],idNext=sgPS->Cells[PSGROUPIDCOL][sgPS->Row];
    //проверка наличия пары состояний
    TADOQuery *rez=DB->SendSQL("Select * from administration.treeconds a where a.IdCond="+idCond+" and a.IdNextCond="+idNext);
    if (rez)//проверка наличия пары состояний
    {
        if (rez->RecordCount)
        {//действие
            DB->SendCommand("delete from administration.treeconds where IdCond='"+idCond+"'and IdNextCond='"+idNext+"'");
            pcStatesSettingsChange(nullptr);
        }else
        {//исключения
            MessageBox(Handle,_T("Состояние отсутствует в списке"),_T("Внимание"),MB_ICONWARNING|MB_OK);
        }
    }
    delete rez;
}
//заполнение сетки
void    TSettings::Fill_Greed   (String sql,TStringGrid *sg,int offset)
{//закончена
    SGClear(sg,offset);
    TADOQuery *rez=DB->SendSQL(sql);
    if (rez&&rez->RecordCount)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            for (int i = 0; i<rez->FieldCount&&i+sg->FixedCols<sg->ColCount+offset; i++)
            {
                sg->Cells[i+sg->FixedCols][sg->RowCount-1]=rez->Fields->operator [](i)->Value.IsNull()?UnicodeString():rez->Fields->operator [](i)->Value.operator UnicodeString();
            }
            sg->RowCount++;
        }
        if (sg->RowCount>sg->FixedRows+1)
        {
            sg->RowCount--;
        }
    }
    delete rez;
}

