object IzdAppenderWnd: TIzdAppenderWnd
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1080#1079#1076#1077#1083#1080#1077
  ClientHeight = 128
  ClientWidth = 221
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 5
    Width = 29
    Height = 13
    Caption = #1047#1072#1082#1072#1079
  end
  object Label2: TLabel
    Left = 114
    Top = 5
    Width = 37
    Height = 13
    Caption = #1055#1072#1088#1090#1080#1103
  end
  object Label3: TLabel
    Left = 8
    Top = 51
    Width = 112
    Height = 13
    Caption = #1054#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077' '#1080#1079#1076#1077#1083#1080#1103
  end
  object Label4: TLabel
    Left = 170
    Top = 5
    Width = 35
    Height = 13
    Caption = #1050#1086#1083'-'#1074#1086
  end
  object ZakazList: TComboBox
    Left = 8
    Top = 24
    Width = 100
    Height = 21
    Style = csDropDownList
    TabOrder = 0
    OnChange = ZakazListChange
  end
  object PartList: TComboBox
    Left = 114
    Top = 24
    Width = 50
    Height = 21
    Style = csDropDownList
    TabOrder = 1
  end
  object Izd: TEdit
    Left = 8
    Top = 70
    Width = 205
    Height = 21
    TabOrder = 2
  end
  object BitBtn2: TBitBtn
    Left = 57
    Top = 97
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 3
  end
  object BitBtn1: TBitBtn
    Left = 138
    Top = 97
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    DoubleBuffered = True
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 4
    OnClick = BitBtn1Click
  end
  object Kol: TEdit
    Left = 170
    Top = 24
    Width = 43
    Height = 21
    NumbersOnly = True
    TabOrder = 5
    Text = '1'
  end
end
