object CalckAddParams: TCalckAddParams
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099
  ClientHeight = 127
  ClientWidth = 135
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Cex: TLabeledEdit
    Left = 8
    Top = 24
    Width = 57
    Height = 21
    EditLabel.Width = 20
    EditLabel.Height = 13
    EditLabel.Caption = #1062#1077#1093
    TabOrder = 0
  end
  object Utch: TLabeledEdit
    Left = 71
    Top = 24
    Width = 58
    Height = 21
    EditLabel.Width = 42
    EditLabel.Height = 13
    EditLabel.Caption = #1059#1095#1072#1089#1090#1086#1082
    TabOrder = 1
  end
  object Percent: TLabeledEdit
    Left = 8
    Top = 67
    Width = 57
    Height = 21
    EditLabel.Width = 43
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1088#1086#1094#1077#1085#1090
    TabOrder = 2
    Text = '100'
  end
  object Kol: TLabeledEdit
    Left = 71
    Top = 67
    Width = 58
    Height = 21
    EditLabel.Width = 35
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1083'-'#1074#1086
    NumbersOnly = True
    TabOrder = 3
    Text = '1'
  end
  object BitBtn1: TBitBtn
    Left = 54
    Top = 94
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
end
