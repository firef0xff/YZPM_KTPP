object Form1: TForm1
  Left = 248
  Top = 139
  Width = 696
  Height = 480
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Shell Dlg 2'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 79
    Align = alTop
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 8
      Width = 281
      Height = 21
      BevelInner = bvNone
      BevelKind = bkSoft
      BevelOuter = bvNone
      TabOrder = 0
    end
    object Button1: TButton
      Left = 296
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Navigate'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 16
      Top = 48
      Width = 75
      Height = 25
      Caption = 'New Page'
      TabOrder = 2
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 96
      Top = 48
      Width = 75
      Height = 25
      Caption = 'Close Page'
      TabOrder = 3
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 176
      Top = 48
      Width = 75
      Height = 25
      Caption = 'Home'
      TabOrder = 4
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 256
      Top = 48
      Width = 75
      Height = 25
      Caption = 'Back'
      TabOrder = 5
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 336
      Top = 48
      Width = 75
      Height = 25
      Caption = 'Forward'
      TabOrder = 6
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 416
      Top = 48
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 7
      OnClick = Button7Click
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 79
    Width = 688
    Height = 374
    Align = alClient
    TabOrder = 1
    OnDragDrop = PageControlDragDrop
    OnDragOver = PageControlDragOver
    OnMouseDown = PageControl1MouseDown
    OnMouseUp = PageControl1MouseUp
  end
end