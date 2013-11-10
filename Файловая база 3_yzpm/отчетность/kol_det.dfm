object koldet: Tkoldet
  Left = 0
  Top = 0
  Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1076#1077#1090#1072#1083#1077#1081
  ClientHeight = 101
  ClientWidth = 324
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object L1: TLabel
    Left = 8
    Top = 8
    Width = 43
    Height = 13
    Caption = #1048#1079#1076#1077#1083#1080#1077
  end
  object L2: TLabel
    Left = 234
    Top = 8
    Width = 29
    Height = 13
    Caption = #1047#1072#1082#1072#1079
  end
  object Label1: TLabel
    Left = 8
    Top = 54
    Width = 35
    Height = 13
    Caption = #1050#1086#1083'-'#1074#1086
  end
  object CB1: TComboBox
    Left = 8
    Top = 27
    Width = 220
    Height = 21
    TabOrder = 0
    OnClick = CB1Click
    OnDblClick = CB1Click
  end
  object CB2: TComboBox
    Left = 234
    Top = 27
    Width = 82
    Height = 21
    TabOrder = 1
    OnChange = CB2Click
    OnClick = CB2Click
  end
  object E1: TEdit
    Left = 8
    Top = 72
    Width = 65
    Height = 21
    NumbersOnly = True
    ReadOnly = True
    TabOrder = 2
  end
  object BitBtn1: TBitBtn
    Left = 241
    Top = 68
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 3
  end
  object BitBtn2: TBitBtn
    Left = 160
    Top = 68
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 4
  end
  object BitBtn3: TBitBtn
    Left = 79
    Top = 68
    Width = 75
    Height = 25
    Caption = #1057#1085#1072#1095#1072#1083#1072
    DoubleBuffered = True
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333444444
      33333333333F8888883F33330000324334222222443333388F3833333388F333
      000032244222222222433338F8833FFFFF338F3300003222222AAAAA22243338
      F333F88888F338F30000322222A33333A2224338F33F8333338F338F00003222
      223333333A224338F33833333338F38F00003222222333333A444338FFFF8F33
      3338888300003AAAAAAA33333333333888888833333333330000333333333333
      333333333333333333FFFFFF000033333333333344444433FFFF333333888888
      00003A444333333A22222438888F333338F3333800003A2243333333A2222438
      F38F333333833338000033A224333334422224338338FFFFF8833338000033A2
      22444442222224338F3388888333FF380000333A2222222222AA243338FF3333
      33FF88F800003333AA222222AA33A3333388FFFFFF8833830000333333AAAAAA
      3333333333338888883333330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 5
    OnClick = FormShow
  end
end
