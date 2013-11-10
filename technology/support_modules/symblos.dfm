object Symbol: TSymbol
  Left = 0
  Top = 0
  Caption = #1057#1087#1077#1094'. '#1089#1080#1084#1074#1086#1083#1099
  ClientHeight = 260
  ClientWidth = 422
  Color = clBtnFace
  Constraints.MaxHeight = 290
  Constraints.MaxWidth = 430
  Constraints.MinHeight = 290
  Constraints.MinWidth = 430
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  DesignSize = (
    422
    260)
  PixelsPerInch = 96
  TextHeight = 13
  object SG1: TStringGrid
    Left = 0
    Top = 0
    Width = 422
    Height = 220
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 10
    DefaultColWidth = 40
    DefaultRowHeight = 40
    FixedCols = 0
    FixedRows = 0
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Autoproject'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnDblClick = SG1DblClick
  end
  object BitBtn1: TBitBtn
    Left = 344
    Top = 227
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 1
  end
  object BitBtn2: TBitBtn
    Left = 263
    Top = 227
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 2
  end
  object E1: TEdit
    Left = 8
    Top = 226
    Width = 249
    Height = 27
    Anchors = [akLeft, akRight, akBottom]
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Autoproject'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
  end
end
