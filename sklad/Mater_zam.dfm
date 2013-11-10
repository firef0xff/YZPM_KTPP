object Mat_zam: TMat_zam
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1047#1072#1084#1077#1085#1072' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
  ClientHeight = 103
  ClientWidth = 285
  Color = clBtnFace
  DefaultMonitor = dmDesktop
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
    Left = 135
    Top = 27
    Width = 20
    Height = 13
    Caption = '--->'
  end
  object old_mat: TLabeledEdit
    Left = 8
    Top = 24
    Width = 121
    Height = 21
    EditLabel.Width = 61
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1090#1072#1088#1099#1081' '#1082#1086#1076
    TabOrder = 0
  end
  object new_mat: TLabeledEdit
    Left = 161
    Top = 24
    Width = 121
    Height = 21
    EditLabel.Width = 55
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1086#1074#1099#1081' '#1082#1086#1076
    TabOrder = 1
  end
  object BitBtn1: TBitBtn
    Left = 207
    Top = 73
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    Default = True
    DoubleBuffered = True
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      333333333333333333333333000033338833333333333333333F333333333333
      0000333911833333983333333388F333333F3333000033391118333911833333
      38F38F333F88F33300003339111183911118333338F338F3F8338F3300003333
      911118111118333338F3338F833338F3000033333911111111833333338F3338
      3333F8330000333333911111183333333338F333333F83330000333333311111
      8333333333338F3333383333000033333339111183333333333338F333833333
      00003333339111118333333333333833338F3333000033333911181118333333
      33338333338F333300003333911183911183333333383338F338F33300003333
      9118333911183333338F33838F338F33000033333913333391113333338FF833
      38F338F300003333333333333919333333388333338FFF830000333333333333
      3333333333333333333888330000333333333333333333333333333333333333
      0000}
    ModalResult = 2
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 2
  end
  object BitBtn2: TBitBtn
    Left = 126
    Top = 73
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 3
    OnClick = BitBtn2Click
  end
  object CB1: TCheckBox
    Left = 8
    Top = 51
    Width = 193
    Height = 17
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1072#1088#1099#1081' ('#1090#1086#1083#1100#1082#1086' '#1076#1083#1103' NA)'
    TabOrder = 4
  end
end
