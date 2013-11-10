unit Unit2;

interface
uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, OleCtrls, SHDocVw, ComCtrls, StdCtrls, ExtCtrls;
type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Edit1: TEdit;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    PageControl1: TPageControl;
    procedure Button2Click(Sender: TObject);
    procedure WebBrowser1NavigateComplete2(Sender: TObject;
      const pDisp: IDispatch; var URL: OleVariant);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure PageControl1Change(Sender: TObject);
    procedure PageControlDragDrop(Sender, Source: TObject; X, Y: Integer);
    procedure PageControlDragOver(Sender, Source: TObject; X, Y: Integer;
      State: TDragState; var Accept: Boolean);
    procedure WebBrowser1DocumentComplete(Sender: TObject;
      const pDisp: IDispatch; var URL: OleVariant);
    procedure FormCreate(Sender: TObject);
    procedure PageControl1MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure PageControl1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
  public
    { Public declarations }
  end;
var
  Form1: TForm1;
  i:integer;
implementation
{$R *.dfm}
procedure TForm1.Button2Click(Sender: TObject);
  var t:TTabSheet;
begin
  t:=TTabSheet.Create(Form1);
  t.PageControl:=PageControl1;
  t.DragMode:=dmAutomatic;
  t.Tag:=integer(TWebBrowser.Create(Form1));
  inc(i);
  t.Caption:='Untitled '+inttostr(i);
  TOleControl(t.Tag).Parent:=t;
  TWebBrowser(t.Tag).align:=alClient;
  TWebBrowser(t.Tag).Visible:=true;
  TWebBrowser(t.Tag).OnNavigateComplete2:=WebBrowser1NavigateComplete2;
  TWebBrowser(t.Tag).OnDocumentComplete:=WebBrowser1DocumentComplete;
  TWebBrowser(t.Tag).GoHome;
end;
procedure TForm1.WebBrowser1NavigateComplete2(Sender: TObject;
  const pDisp: IDispatch; var URL: OleVariant);
begin
  Edit1.Text:=URL;
end;
procedure TForm1.Button3Click(Sender: TObject);
begin
  if PageControl1.ActivePage=nil then exit;
  TWebBrowser(PageControl1.ActivePage.Tag).free;
  PageControl1.ActivePage.Free;
end;
procedure TForm1.Button4Click(Sender: TObject);
begin
  if PageControl1.ActivePage=nil then exit;
  TWebBrowser(PageControl1.ActivePage.Tag).GoHome;
end;
procedure TForm1.Button5Click(Sender: TObject);
begin
  if PageControl1.ActivePage=nil then exit;
  TWebBrowser(PageControl1.ActivePage.Tag).GoBack;
end;
procedure TForm1.Button6Click(Sender: TObject);
begin
  if PageControl1.ActivePage=nil then exit;
  TWebBrowser(PageControl1.ActivePage.Tag).GoForward;
end;
procedure TForm1.Button7Click(Sender: TObject);
begin
  if PageControl1.ActivePage=nil then exit;
  TWebBrowser(PageControl1.ActivePage.Tag).Refresh;
end;
procedure TForm1.Button1Click(Sender: TObject);
begin
  if PageControl1.ActivePage=nil then exit;
  TWebBrowser(PageControl1.ActivePage.Tag).Navigate(Edit1.Text);
end;
procedure TForm1.PageControl1Change(Sender: TObject);
begin
  Edit1.Text:=TWebBrowser(PageControl1.ActivePage.Tag).LocationURL;
end;
procedure TForm1.PageControlDragDrop(Sender, Source: TObject; X, Y: Integer);
begin
  if (Source is TPageControl) and ((PageControl1.ActivePageIndex<>PageControl1.IndexOfTabAt(x,y))) then
    begin
     PageControl1.ActivePage.PageIndex:=PageControl1.IndexOfTabAt(x,y);
     PageControl1.EndDrag(true);
     PageControl1.tag:=0;
    end;
  PageControl1Change(nil);
end;
procedure TForm1.PageControlDragOver(Sender, Source: TObject; X,
  Y: Integer; State: TDragState; var Accept: Boolean);
begin
  Accept:=(Source is TPageControl);
end;
procedure TForm1.WebBrowser1DocumentComplete(Sender: TObject;
  const pDisp: IDispatch; var URL: OleVariant);
begin
  Edit1.Text:=URL;
end;
procedure TForm1.FormCreate(Sender: TObject);
begin
  i:=0;
end;
procedure TForm1.PageControl1MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if PageControl1.tag=1 then
    PageControl1.EndDrag(false);
  PageControl1.tag:=0;
end;
procedure TForm1.PageControl1MouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if PageControl1.tag<>1 then
    PageControl1.BeginDrag(true);
  PageControl1.tag:=1;
end;
end.
