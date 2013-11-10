object Simple_fraction: TSimple_fraction
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Simple_fraction'
  ClientHeight = 439
  ClientWidth = 384
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 135
    Top = 34
    Width = 14
    Height = 30
    Caption = '='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Arial Black'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = Label1Click
  end
  object Label2: TLabel
    Left = 155
    Top = 23
    Width = 220
    Height = 30
    Caption = '____________________'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Arial Black'
    Font.Style = [fsBold, fsItalic, fsUnderline]
    ParentFont = False
  end
  object isx: TLabeledEdit
    Left = 8
    Top = 32
    Width = 121
    Height = 31
    EditLabel.Width = 30
    EditLabel.Height = 13
    EditLabel.Caption = #1063#1080#1089#1083#1086
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial Black'
    Font.Style = [fsBold]
    MaxLength = 9
    ParentFont = False
    TabOrder = 0
    OnKeyPress = isxKeyPress
  end
  object Chislitel: TEdit
    Left = 153
    Top = 11
    Width = 224
    Height = 31
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial Black'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
  end
  object Znamenatel: TEdit
    Left = 153
    Top = 56
    Width = 224
    Height = 31
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial Black'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 2
  end
  object Memo1: TMemo
    Left = 8
    Top = 93
    Width = 368
    Height = 338
    Lines.Strings = (
      'Memo1')
    TabOrder = 3
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;User ID=root;Data' +
      ' Source=raschet;Initial Catalog=raschet'
    Provider = 'MSDASQL.1'
    Left = 104
    Top = 72
  end
end
