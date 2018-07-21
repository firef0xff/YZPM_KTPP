object LocationForm: TLocationForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1052#1077#1089#1090#1086#1088#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1077
  ClientHeight = 132
  ClientWidth = 197
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 43
    Height = 13
    Caption = #1050#1072#1073#1080#1085#1077#1090
  end
  object Label2: TLabel
    Left = 8
    Top = 35
    Width = 77
    Height = 13
    Caption = #1064#1082#1072#1092'/'#1089#1090#1077#1083#1083#1072#1078
  end
  object Label3: TLabel
    Left = 8
    Top = 62
    Width = 31
    Height = 13
    Caption = #1055#1086#1083#1082#1072
  end
  object _eLocationCab: TEdit
    Left = 91
    Top = 8
    Width = 96
    Height = 21
    TabOrder = 0
  end
  object _bChangeLocation: TButton
    Left = 8
    Top = 101
    Width = 179
    Height = 25
    Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
    TabOrder = 3
    OnClick = _bChangeLocationClick
  end
  object _eLocationStack: TEdit
    Left = 91
    Top = 35
    Width = 96
    Height = 21
    TabOrder = 1
  end
  object _eLocationRack: TEdit
    Left = 91
    Top = 62
    Width = 96
    Height = 21
    TabOrder = 2
  end
end
