object Sel_params_agr: TSel_params_agr
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1090#1073#1086#1088#1072
  ClientHeight = 476
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
    476)
  PixelsPerInch = 96
  TextHeight = 13
  object Ka1c: TSpeedButton
    Left = 97
    Top = 318
    Width = 23
    Height = 22
    Caption = '1'#1057
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = Ka1cClick
  end
  object ka_name: TEdit
    Left = 8
    Top = 341
    Width = 281
    Height = 21
    ReadOnly = True
    TabOrder = 0
    OnDblClick = Ka1cClick
  end
  object predm_dog: TComboBox
    Left = 150
    Top = 291
    Width = 139
    Height = 21
    TabOrder = 1
  end
  object isp_list: TComboBox
    Left = 8
    Top = 291
    Width = 136
    Height = 21
    Style = csDropDownList
    TabOrder = 2
  end
  object podr_list: TComboBox
    Left = 8
    Top = 242
    Width = 281
    Height = 22
    Style = csOwnerDrawFixed
    TabOrder = 3
  end
  object dog_num: TEdit
    Left = 109
    Top = 27
    Width = 180
    Height = 21
    TabOrder = 4
  end
  object dog_type: TComboBox
    Left = 8
    Top = 27
    Width = 95
    Height = 21
    ItemIndex = 0
    TabOrder = 5
    Text = #1044#1086#1075#1086#1074#1086#1088
    Items.Strings = (
      #1044#1086#1075#1086#1074#1086#1088
      #1055#1080#1089#1100#1084#1086
      #1050#1086#1085#1090#1088#1072#1082#1090)
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 54
    Width = 281
    Height = 48
    TabOrder = 6
    object Label9: TLabel
      Left = 143
      Top = 27
      Width = 16
      Height = 13
      Caption = #1076#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 9
      Top = 27
      Width = 14
      Height = 13
      Caption = #1086#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object cd_max: TDateTimePicker
      Left = 164
      Top = 23
      Width = 107
      Height = 21
      Date = 41059.554132534720000000
      Time = 41059.554132534720000000
      TabOrder = 0
    end
    object cd_min: TDateTimePicker
      Left = 29
      Top = 23
      Width = 107
      Height = 21
      Date = 41059.554132534720000000
      Time = 41059.554132534720000000
      TabOrder = 1
    end
    object b_cd: TCheckBox
      Left = 3
      Top = 0
      Width = 149
      Height = 17
      Caption = #1044#1072#1090#1072' '#1089#1086#1079#1076#1072#1085#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 108
    Width = 281
    Height = 50
    TabOrder = 7
    object Label6: TLabel
      Left = 142
      Top = 29
      Width = 16
      Height = 13
      Caption = #1076#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 9
      Top = 29
      Width = 14
      Height = 13
      Caption = #1086#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object sign_max: TDateTimePicker
      Left = 164
      Top = 26
      Width = 107
      Height = 21
      Date = 41059.554132534720000000
      Time = 41059.554132534720000000
      TabOrder = 0
    end
    object sign_min: TDateTimePicker
      Left = 29
      Top = 26
      Width = 107
      Height = 21
      Date = 41059.554132534720000000
      Time = 41059.554132534720000000
      TabOrder = 1
    end
    object b_sign_dt: TCheckBox
      Left = 3
      Top = 3
      Width = 168
      Height = 17
      Caption = #1044#1072#1090#1072' '#1087#1086#1076#1087#1080#1089#1072#1085#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 164
    Width = 281
    Height = 49
    TabOrder = 8
    object Label8: TLabel
      Left = 142
      Top = 29
      Width = 16
      Height = 13
      Caption = #1076#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 9
      Top = 29
      Width = 14
      Height = 13
      Caption = #1086#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object b_summ: TCheckBox
      Left = 3
      Top = 3
      Width = 168
      Height = 17
      Caption = #1057#1091#1084#1084#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object summ_min: TEdit
      Left = 29
      Top = 26
      Width = 107
      Height = 21
      TabOrder = 1
    end
    object summ_max: TEdit
      Left = 164
      Top = 26
      Width = 107
      Height = 21
      TabOrder = 2
    end
  end
  object b_type: TCheckBox
    Left = 8
    Top = 4
    Width = 46
    Height = 17
    Caption = #1042#1080#1076':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
  end
  object b_dog_num: TCheckBox
    Left = 109
    Top = 4
    Width = 121
    Height = 17
    Caption = #1053#1086#1084#1077#1088' '#1076#1086#1075#1086#1074#1086#1088#1072':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 10
  end
  object b_isp: TCheckBox
    Left = 8
    Top = 268
    Width = 121
    Height = 17
    Caption = #1048#1089#1087#1086#1083#1085#1080#1090#1077#1083#1100':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 11
  end
  object b_podr: TCheckBox
    Left = 8
    Top = 219
    Width = 121
    Height = 17
    Caption = #1055#1086#1076#1088#1072#1079#1076#1077#1083#1077#1085#1080#1077':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
  end
  object b_predm: TCheckBox
    Left = 150
    Top = 268
    Width = 136
    Height = 17
    Caption = #1055#1088#1077#1076#1084#1077#1090' '#1076#1086#1075#1086#1074#1086#1088#1072':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 13
  end
  object b_ka: TCheckBox
    Left = 8
    Top = 318
    Width = 95
    Height = 17
    Caption = #1050#1086#1085#1090#1088#1072#1075#1077#1085#1090':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 14
  end
  object b_signed: TRadioGroup
    Left = 8
    Top = 366
    Width = 281
    Height = 51
    Caption = #1055#1086#1076#1087#1080#1089#1072#1085#1080#1077
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      #1042#1089#1077
      #1053#1077' '#1087#1086#1076#1087#1080#1089#1072#1085#1085#1099#1077
      #1055#1086#1076#1087#1080#1089#1072#1085#1085#1099#1077)
    TabOrder = 15
  end
  object b_active: TCheckBox
    Left = 8
    Top = 423
    Width = 209
    Height = 17
    Caption = #1058#1086#1083#1100#1082#1086' '#1076#1077#1081#1089#1090#1074#1091#1102#1097#1080#1077' '#1076#1086#1075#1086#1074#1086#1088#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 16
  end
  object OK: TBitBtn
    Left = 132
    Top = 446
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
    TabOrder = 17
    OnClick = OKClick
  end
  object Cancel: TBitBtn
    Left = 213
    Top = 446
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
    TabOrder = 18
  end
end
