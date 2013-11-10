object Sel_params_prod: TSel_params_prod
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1090#1073#1086#1088#1072
  ClientHeight = 263
  ClientWidth = 296
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  DesignSize = (
    296
    263)
  PixelsPerInch = 96
  TextHeight = 13
  object Ka1c: TSpeedButton
    Left = 100
    Top = 104
    Width = 61
    Height = 22
    Caption = #1042#1099#1073#1088#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = Ka1cClick
  end
  object dog_select: TSpeedButton
    Left = 175
    Top = 4
    Width = 75
    Height = 22
    Caption = #1042#1099#1073#1088#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = dog_selectClick
  end
  object ka_name: TEdit
    Left = 7
    Top = 127
    Width = 281
    Height = 21
    ReadOnly = True
    TabOrder = 0
    OnDblClick = Ka1cClick
  end
  object podr_list: TComboBox
    Left = 8
    Top = 180
    Width = 281
    Height = 22
    Style = csOwnerDrawFixed
    TabOrder = 1
  end
  object dog_num: TEdit
    Left = 95
    Top = 27
    Width = 193
    Height = 21
    TabOrder = 2
    OnChange = dog_numChange
  end
  object b_dog_num: TCheckBox
    Left = 95
    Top = 4
    Width = 74
    Height = 17
    Caption = #1044#1086#1075#1086#1074#1086#1088':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
  end
  object b_podr: TCheckBox
    Left = 8
    Top = 157
    Width = 121
    Height = 17
    Caption = #1055#1086#1076#1088#1072#1079#1076#1077#1083#1077#1085#1080#1077':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
  end
  object b_ka: TCheckBox
    Left = 7
    Top = 104
    Width = 95
    Height = 17
    Caption = #1050#1086#1085#1090#1088#1072#1075#1077#1085#1090':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
  end
  object b_active: TCheckBox
    Left = 8
    Top = 208
    Width = 209
    Height = 17
    Caption = #1058#1086#1083#1100#1082#1086' '#1076#1077#1081#1089#1090#1074#1091#1102#1097#1080#1077' '#1076#1086#1075#1086#1074#1086#1088#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
  end
  object OK: TBitBtn
    Left = 132
    Top = 231
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1055#1088#1080#1085#1103#1090#1100
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
    ModalResult = 1
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 7
    OnClick = OKClick
  end
  object Cancel: TBitBtn
    Left = 213
    Top = 231
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
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
    TabOrder = 8
  end
  object zak: TCheckBox
    Left = 8
    Top = 4
    Width = 81
    Height = 17
    Caption = #1047#1072#1082#1072#1079' '#8470':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
  end
  object Zak_numb: TEdit
    Left = 8
    Top = 27
    Width = 81
    Height = 21
    NumbersOnly = True
    TabOrder = 10
    OnDblClick = Ka1cClick
  end
  object zak_name: TEdit
    Left = 8
    Top = 77
    Width = 280
    Height = 21
    TabOrder = 11
    OnDblClick = Ka1cClick
  end
  object name: TCheckBox
    Left = 8
    Top = 54
    Width = 113
    Height = 17
    Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
  end
end
