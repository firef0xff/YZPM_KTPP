#pragma hdrstop
#include "functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void MkPjDir(AnsiString subpart,AnsiString part)
{
AnsiString newfold,fold="";
while (subpart.Pos("\\")!=0)
    {
    newfold=subpart.SubString(1,subpart.Pos("\\"));
    subpart.Delete(1,subpart.Pos("\\"));
    MkDir(part+fold+newfold);
    fold=fold+newfold;
    }
}
AnsiString GetDirName (void)
{
randomize();
String part="";
int i,level=random(10);
for (i=0; i <= level; i++)
{
part=part+IntToStr(random(40))+"\\";
}
return part;
}
AnsiString GetFileName (void)
{
randomize();
AnsiString name=IntToStr(random(99999999))+".bdf";
return name;
}
bool DeleteDir(AnsiString DirName)
{
TSearchRec sr;
if (DirName.Length())
 {
 if (!FindFirst(DirName+"\\*.*",faAnyFile,sr))
 do
  {
  if (!(sr.Name=="." || sr.Name==".."))// это удалять не надо
   if (((sr.Attr & faDirectory) == faDirectory ) ||
   (sr.Attr == faDirectory))// найдена папка
    {
    FileSetAttr(DirName+"\\"+sr.Name, faDirectory );// сброс всяких read-only
    DeleteDir(DirName+"\\"+sr.Name);//рекурсивно удаляем содержимое
    RemoveDir(DirName + "\\"+sr.Name);// удаляем теперь уже пустую папку
    }
    else// иначе найден файл
    {
    FileSetAttr(DirName+"\\"+sr.Name, 0);// сброс всяких read-only
    DeleteFile(DirName+"\\"+sr.Name);// удаляем файл
    }
  }
 while (!FindNext(sr));// ищем опять, пока не найдем все
 FindClose(sr);
 }
RemoveDir(DirName);
return true;
}

AnsiString ekran (AnsiString inpstr)
{
int i;
for (i = 1; i<=inpstr.Length(); i++)
    {
    if (inpstr.operator [](i)=='\\'||
        inpstr.operator [](i)=='\`'||
        inpstr.operator [](i)=='\"'||
        inpstr.operator [](i)=='\''/*||
        inpstr.operator [](i)=='\%'*/)
        {
         inpstr.Insert("\\",i);
         i++;
        }
    /*if (inpstr.operator [](i)==',')
        {
         inpstr.Delete(i,1);
         inpstr.Insert(".",i);
         i++;
        } */
    }
return inpstr;
}
AnsiString Replace (AnsiString st,AnsiString Old,AnsiString New)
{
int i;
String sub;
for (i=1; i <=st.Length(); i++)
    {
    sub=st.SubString(i,Old.Length());
    if (sub==Old)
        {
        st.Delete(i,Old.Length());
        st.Insert(New,i);
        i+=New.Length()-1;
        }
    }
return st;
}
AnsiString Replace (AnsiString st,AnsiString Old,AnsiString New,int pos,int count)
{
int i,cnt=0;
String sub;
for (i=pos; i <=st.Length()&&cnt<count; i++)
    {
    sub=st.SubString(i,Old.Length());
    if (sub==Old)
        {
        st.Delete(i,Old.Length());
        st.Insert(New,i);
        i+=New.Length()-1;
        cnt++;
        }
    }
return st;
}
AnsiString GetOnlyNum(String st)
{
int i;
for (i = 1; i <=st.Length(); i++)
    {
    if (!isdigit(st[i]))
        {
        st.Delete(i,1);
        i--;
        }
    }
return st;
}
bool   ischar (const char ch)
{
String str="йцукенгшщзхъфывапролджэячсмитьбюёqwertyuiopasdfghjklzxcvbnm";
if (str.Pos(LowerCase(ch)))
    {
    return true;
    }else
    {
    return false;
    }
}
bool   isdigit(const char ch)
{
String str="0123456789";
if (str.Pos(LowerCase(ch)))
    {
    return true;
    }else
    {
    return false;
    }
}

AnsiString GostToVin(AnsiString Gost)
{
String tmp=Gost;
Gost=Replace(Gost," ","");
bool isp=false;    // показывает может ли отсутствовать исполнение в обозначении
if (Trim(Gost)==""){return "";} else
    {
    if (Gost.UpperCase().Pos("ПЕШК"))
        {
        Gost=Gost.SubString(Gost.UpperCase().Pos("ПЕШК"),Gost.Length()-Gost.UpperCase().Pos("ПЕШК")+1);
        Gost.Insert("97",Gost.UpperCase().Pos("ПЕШК"));
        Gost.Delete(Gost.UpperCase().Pos("ПЕШК"),4);
        isp=true;
        }
    if (Gost.UpperCase().Pos("ГКНЮ")!=0)
        {
        Gost=Gost.SubString(Gost.UpperCase().Pos("ГКНЮ"),Gost.Length()-Gost.UpperCase().Pos("ГКНЮ")+1);
        Gost.Insert("95",Gost.UpperCase().Pos("ГКНЮ"));   //находим в строке буквенное обозначение и меняем на цифровое
        Gost.Delete(Gost.UpperCase().Pos("ГКНЮ"),4);
        isp=true;
        }
    if (Gost.UpperCase().Pos("НАЦВ")!=0)
        {
        Gost=Gost.SubString(Gost.UpperCase().Pos("НАЦВ"),Gost.Length()-Gost.UpperCase().Pos("НАЦВ")+1);
        Gost.Insert("85",Gost.UpperCase().Pos("НАЦВ"));
        Gost.Delete(Gost.UpperCase().Pos("НАЦВ"),4);
        isp=true;
        }
    if (Gost.UpperCase().Pos("НЕИА")!=0)
        {
        Gost=Gost.SubString(Gost.UpperCase().Pos("НЕИА"),Gost.Length()-Gost.UpperCase().Pos("НЕИА")+1);
        Gost.Insert("98",Gost.UpperCase().Pos("НЕИА"));
        Gost.Delete(Gost.UpperCase().Pos("НЕИА"),4);
        isp=true;
        }
    if (!isdigit(Gost[1]))
        {
        return tmp;
        }
    Gost=GetGostNum(Gost);
    Gost=Gost.SubString(1,15);
    if (Gost.Length()<=15&&Gost.Length()>5)
        {
        if (isp)
            {
            while (Gost.Length()<15)
                {Gost=Gost+"0";}     // если в обозначении отсутствует номер исполнения(нулевое исполнение) то добиваем конец нулями
            }else
            {
            while (Gost.Length()<15)
                {Gost="0"+Gost;}     // если трока меньше 15 символов добиваем нулями (случай с обозначением стандартных или покупных изделий)
            }
        } else return tmp;
    }
 return Gost;
}
AnsiString GostToInt(AnsiString Gost)
{
String tmp=Gost;
Gost=Replace(Gost," ","");    // показывает может ли отсутствовать исполнение в обозначении
if (Trim(Gost)==""){return "";} else
    {
    if (Gost.UpperCase().Pos("ПЕШК"))
        {
        Gost=Gost.SubString(Gost.UpperCase().Pos("ПЕШК"),Gost.Length()-Gost.UpperCase().Pos("ПЕШК")+1);
        Gost.Insert("97",Gost.UpperCase().Pos("ПЕШК"));
        Gost.Delete(Gost.UpperCase().Pos("ПЕШК"),4);
        }
    if (Gost.UpperCase().Pos("ГКНЮ")!=0)
        {
        Gost=Gost.SubString(Gost.UpperCase().Pos("ГКНЮ"),Gost.Length()-Gost.UpperCase().Pos("ГКНЮ")+1);
        Gost.Insert("95",Gost.UpperCase().Pos("ГКНЮ"));   //находим в строке буквенное обозначение и меняем на цифровое
        Gost.Delete(Gost.UpperCase().Pos("ГКНЮ"),4);
        }
    if (Gost.UpperCase().Pos("НАЦВ")!=0)
        {
        Gost=Gost.SubString(Gost.UpperCase().Pos("НАЦВ"),Gost.Length()-Gost.UpperCase().Pos("НАЦВ")+1);
        Gost.Insert("85",Gost.UpperCase().Pos("НАЦВ"));
        Gost.Delete(Gost.UpperCase().Pos("НАЦВ"),4);
        }
    if (Gost.UpperCase().Pos("НЕИА")!=0)
        {
        Gost=Gost.SubString(Gost.UpperCase().Pos("НЕИА"),Gost.Length()-Gost.UpperCase().Pos("НЕИА")+1);
        Gost.Insert("98",Gost.UpperCase().Pos("НЕИА"));
        Gost.Delete(Gost.UpperCase().Pos("НЕИА"),4);
        }
    if (!isdigit(Gost[1]))
        {
        return tmp;
        }
    Gost=GetGostNum(Gost);
    return Gost;
    }
}
AnsiString GetGostNum(AnsiString st)
{
int i;
for (i = 1; i <=st.Length(); i++)
    {
    if (!isdigit(st[i]))
        {
        if (ischar(st[i]))
            {
            return st.SubString(1,i-1);
            }
        st.Delete(i,1);
        i--;
        }
    }
return st;
}
AnsiString VinToGost (AnsiString Vin)
{
if (Vin.Length()!=15||GetOnlyNum(Vin).Length()!=Vin.Length()) {return Vin;}
if (Vin.SubString(1,6)=="000000")
    {
    while (Vin[1]=='0'&&Vin.Length()>6)
        {
        Vin.Delete(1,1);
        }
    return Vin;
    }
String s1,s2,s3,s4,s5,s6,s7;
int type=0;
if (Trim(Vin)==""){return "";}
s1=Vin.SubString(1,2);
s2=Vin.SubString(3,1);
s3=Vin.SubString(4,3);
s4=Vin.SubString(7,2);
s5=Vin.SubString(9,2);
s6=Vin.SubString(11,3);
s7=Vin.SubString(14,2);
if (s1=="85") {s1="НАЦВ";type=1;}
if (s1=="95") {s1="ГКНЮ";type=1;}
if (s1=="97") {s1="ПЕШК";type=1;}
if (s1=="98") {s1="НЕИА";type=1;}
switch (type)
    {
    case 0:{return s1+s2+"."+s3+"."+s4+"."+s5+"."+s6+"-"+s7;}
    case 1:{return s1+"."+s2+"."+s3+"."+s4+"."+s5+"."+s6+"-"+s7;}
default: return Vin;
    }
}

void AutoWidthSG(TStringGrid *sg,int minwdth)
{
int i,j,NewWidth;
for (i = 0; i <sg->ColCount; i++)
    {
    sg->ColWidths[i]=sg->DefaultColWidth;
    for (j=0; j <sg->RowCount; j++)
        {
        sg->Canvas->Font->Charset=sg->Font->Charset;
        sg->Canvas->Font->Color=sg->Font->Color;
        sg->Canvas->Font->Height=sg->Font->Height;
        sg->Canvas->Font->Name=sg->Font->Name;
        sg->Canvas->Font->Orientation=sg->Font->Orientation;
        sg->Canvas->Font->Pitch=sg->Font->Pitch;
        sg->Canvas->Font->Quality=sg->Font->Quality;
        sg->Canvas->Font->Size=sg->Font->Size;
        sg->Canvas->Font->Style=sg->Font->Style;
        NewWidth=sg->Canvas->TextWidth(sg->Cells[i][j])+5;
        if (sg->ColWidths[i]<NewWidth&&NewWidth>sg->DefaultColWidth)
            {sg->ColWidths[i]=NewWidth;}
        if (i&&sg->ColWidths[i]<minwdth)
            {sg->ColWidths[i]=minwdth;}//минимальный размерчик под комбо
        }
    }
}
void SGClear (TStringGrid *SG,int RightOfset)
{
int i,j;
for (i = SG->FixedRows; i < SG->RowCount; i++)
    {
    for (j=0; j < SG->ColCount+RightOfset; j++)
        {
        SG->Cells[j][i]="";
        }
    }
SG->RowCount=SG->FixedRows+1;
}

template<typename T>
void shellSort(T a[], long size)
{
long inc,i,j,seq[40];
/*for (i = 0; i < 40; i++)
    {
    seq[i]=0;
    } */
int s;
// вычисление последовательности приращений
s = increment(seq, size);
while (s >= 0)
    {
    // сортировка вставками с инкрементами inc[]
    inc = seq[s--];
    for (i = inc; i < size; i++)
        {
        for (j = i-inc; (j >= 0) && (a[j] > a[j+inc]); j -= inc)
            {
            change(a[j+inc],a[j]);
            }
        }
    }
}
int increment(long inc[], long size)
{
int p1, p2, p3, s;
p1 = p2 = p3 = 1;
s = -1;
do
    {
    if (++s % 2)
        {
        inc[s] = 8*p1 - 6*p2 + 1;
        } else
        {
        inc[s] = 9*p1 - 9*p3 + 1;
        p2 *= 2;
        p3 *= 2;
        }
    p1 *= 2;
    }
while(3*inc[s] < size);
return s > 0 ? --s : 0;
}
template<typename T>
void change (T &el1,T &el2)
{
   T temp=el1;
    el1=el2;
    el2=temp;
}

template<typename T>
void insertSort (T a[], long size)
{
long prev,curr;
for (curr=1; curr < size; curr++)
    {
    for (prev=curr-1; (prev>=0)&&(a[prev]>a[prev+1]); prev--)
        {
        change(a[prev+1],a[prev]);
        }
    }

}

void    WordWrap        (std::list<std::string> &out,std::string in,const size_t max_len, std::string delimeter = " ")
{
    out.clear();
    while (size_t len=in.size())
    {
        if (max_len>=len)
        {
            out.push_back(in);
            in="";
        }
        else
        {
            size_t pos = in.find_last_of(delimeter, max_len);
            size_t delim_ofset = delimeter.size();
            if (pos == std::string::npos)
            {
                //обрезаем по сайзу
                pos = max_len-1;
                delim_ofset = 0;
            }
            //обрезаем по разделителю

            out.push_back(in.substr(0, pos));
            in = in.substr(pos+delim_ofset, in.size());
        }
    }
}
