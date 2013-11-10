object Zak_prop: TZak_prop
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsSizeToolWin
  ClientHeight = 214
  ClientWidth = 496
  Color = clBtnFace
  Constraints.MaxHeight = 1024
  Constraints.MaxWidth = 504
  Constraints.MinHeight = 240
  Constraints.MinWidth = 504
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Ad_composition: TGroupBox
    Left = 0
    Top = 216
    Width = 496
    Height = 2
    Align = alClient
    Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1081' '#1089#1086#1089#1090#1072#1074
    TabOrder = 0
    ExplicitLeft = 3
    ExplicitTop = 213
    ExplicitWidth = 490
    ExplicitHeight = 119
    object StringGrid1: TStringGrid
      Left = 75
      Top = 15
      Width = 419
      Height = 17
      Align = alClient
      DefaultColWidth = 16
      DefaultRowHeight = 16
      RowCount = 2
      TabOrder = 0
      ExplicitHeight = 102
    end
    object Panel1: TPanel
      Left = 2
      Top = 15
      Width = 73
      Height = 17
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 1
      ExplicitHeight = 102
      object ComboBox3: TComboBox
        Left = 3
        Top = 0
        Width = 68
        Height = 21
        Style = csDropDownList
        ItemIndex = 0
        TabOrder = 0
        Text = #1074' '#1090'.'#1095'.:'
        Items.Strings = (
          #1074' '#1090'.'#1095'.:'
          #1074' '#1089#1086#1089#1090#1072#1074#1077':')
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 496
    Height = 216
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = 417
    ExplicitTop = 8
    ExplicitWidth = 185
    ExplicitHeight = 41
    DesignSize = (
      496
      216)
    object Prim_box: TGroupBox
      Left = 295
      Top = 55
      Width = 198
      Height = 50
      Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
      TabOrder = 1
      object Memo1: TMemo
        Left = 2
        Top = 15
        Width = 194
        Height = 33
        Align = alClient
        BevelEdges = [beLeft, beTop]
        TabOrder = 0
      end
    end
    object Pokovki: TGroupBox
      Left = 338
      Top = 111
      Width = 155
      Height = 102
      Caption = #1055#1086#1082#1086#1074#1082#1080
      Constraints.MaxHeight = 102
      Constraints.MaxWidth = 155
      Constraints.MinHeight = 102
      Constraints.MinWidth = 155
      TabOrder = 2
      Visible = False
      object Label3: TLabel
        Left = 3
        Top = 16
        Width = 64
        Height = 13
        Caption = #1042#1080#1076' '#1087#1086#1082#1086#1074#1082#1080
      end
      object ComboBox2: TComboBox
        Left = 3
        Top = 33
        Width = 146
        Height = 21
        Style = csDropDownList
        TabOrder = 0
      end
      object LabeledEdit4: TLabeledEdit
        Left = 3
        Top = 75
        Width = 70
        Height = 21
        EditLabel.Width = 61
        EditLabel.Height = 13
        EditLabel.Caption = #1042#1077#1089' 1 '#1096#1090', '#1082#1075
        TabOrder = 1
      end
      object LabeledEdit9: TLabeledEdit
        Left = 79
        Top = 75
        Width = 70
        Height = 21
        EditLabel.Width = 49
        EditLabel.Height = 13
        EditLabel.Caption = #1062#1077#1085#1072' 1 '#1082#1075
        TabOrder = 2
      end
    end
    object Product: TGroupBox
      Left = 3
      Top = 3
      Width = 286
      Height = 102
      Caption = #1048#1079#1076#1077#1083#1080#1077
      Constraints.MaxHeight = 102
      Constraints.MaxWidth = 286
      Constraints.MinHeight = 102
      Constraints.MinWidth = 286
      TabOrder = 3
      object LabeledEdit1: TLabeledEdit
        Left = 3
        Top = 32
        Width = 278
        Height = 21
        EditLabel.Width = 73
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = []
        EditLabel.ParentFont = False
        TabOrder = 0
      end
      object LabeledEdit2: TLabeledEdit
        Left = 3
        Top = 75
        Width = 151
        Height = 21
        EditLabel.Width = 67
        EditLabel.Height = 13
        EditLabel.Caption = #1054#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077
        TabOrder = 1
      end
      object LabeledEdit3: TLabeledEdit
        Left = 160
        Top = 75
        Width = 121
        Height = 21
        EditLabel.Width = 37
        EditLabel.Height = 13
        EditLabel.Caption = #1048#1085#1076#1077#1082#1089
        TabOrder = 2
      end
    end
    object Zak_no: TGroupBox
      Left = 295
      Top = 3
      Width = 86
      Height = 46
      Caption = #1047#1072#1082#1072#1079' '#8470
      Color = clBtnFace
      Constraints.MaxHeight = 46
      Constraints.MaxWidth = 86
      Constraints.MinHeight = 46
      Constraints.MinWidth = 86
      ParentBackground = False
      ParentColor = False
      TabOrder = 4
      object Zak_pref: TComboBox
        Left = 3
        Top = 19
        Width = 38
        Height = 21
        Style = csDropDownList
        TabOrder = 0
      end
      object Edit1: TEdit
        Left = 47
        Top = 19
        Width = 34
        Height = 21
        MaxLength = 4
        NumbersOnly = True
        TabOrder = 1
      end
    end
    object Zak_params: TGroupBox
      Left = 3
      Top = 111
      Width = 329
      Height = 102
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1079#1072#1082#1072#1079#1072
      Constraints.MaxHeight = 102
      Constraints.MaxWidth = 329
      Constraints.MinHeight = 102
      Constraints.MinWidth = 329
      TabOrder = 5
      object Label1: TLabel
        Left = 81
        Top = 17
        Width = 41
        Height = 13
        Caption = #1045#1076'. '#1080#1079#1084'.'
      end
      object Label2: TLabel
        Left = 152
        Top = 17
        Width = 36
        Height = 13
        Caption = #1047#1072#1103#1074#1082#1072
      end
      object z_kol: TLabeledEdit
        Left = 5
        Top = 33
        Width = 70
        Height = 21
        EditLabel.Width = 35
        EditLabel.Height = 13
        EditLabel.Caption = #1050#1086#1083'-'#1074#1086
        NumbersOnly = True
        TabOrder = 0
      end
      object LabeledEdit5: TLabeledEdit
        Left = 5
        Top = 75
        Width = 70
        Height = 21
        EditLabel.Width = 56
        EditLabel.Height = 13
        EditLabel.Caption = #1062#1077#1085#1072' 1 '#1096#1090'.'
        TabOrder = 1
      end
      object ComboBox1: TComboBox
        Left = 81
        Top = 33
        Width = 45
        Height = 21
        Style = csDropDownList
        TabOrder = 2
      end
      object LabeledEdit6: TLabeledEdit
        Left = 81
        Top = 75
        Width = 66
        Height = 21
        EditLabel.Width = 31
        EditLabel.Height = 13
        EditLabel.Caption = #1057#1091#1084#1084#1072
        TabOrder = 3
      end
      object LabeledEdit7: TLabeledEdit
        Left = 241
        Top = 75
        Width = 82
        Height = 21
        EditLabel.Width = 70
        EditLabel.Height = 13
        EditLabel.Caption = #1044#1072#1090#1072' '#1088#1072#1089#1095#1077#1090#1072
        TabOrder = 4
      end
      object LabeledEdit8: TLabeledEdit
        Left = 153
        Top = 75
        Width = 82
        Height = 21
        EditLabel.Width = 77
        EditLabel.Height = 13
        EditLabel.Caption = #1057#1077#1073#1077#1089#1090#1086#1080#1084#1086#1089#1090#1100
        TabOrder = 5
      end
      object ButtonedEdit1: TButtonedEdit
        Left = 153
        Top = 33
        Width = 170
        Height = 21
        ReadOnly = True
        TabOrder = 6
      end
    end
    object Cancel: TBitBtn
      Left = 416
      Top = 34
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
      TabOrder = 6
    end
    object OK: TBitBtn
      Left = 417
      Top = 3
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
    end
    object Facilities: TGroupBox
      Left = 338
      Top = 111
      Width = 110
      Height = 102
      Caption = #1059#1089#1083#1091#1075#1080
      Constraints.MaxHeight = 102
      Constraints.MaxWidth = 110
      Constraints.MinHeight = 102
      Constraints.MinWidth = 110
      TabOrder = 0
      Visible = False
      object LabeledEdit10: TLabeledEdit
        Left = 3
        Top = 35
        Width = 102
        Height = 21
        EditLabel.Width = 91
        EditLabel.Height = 13
        EditLabel.Caption = #1058#1088#1091#1076#1086#1077#1084#1082#1086#1089#1090#1100' '#1085'/'#1095
        TabOrder = 0
      end
      object LabeledEdit11: TLabeledEdit
        Left = 3
        Top = 75
        Width = 102
        Height = 21
        EditLabel.Width = 104
        EditLabel.Height = 13
        EditLabel.Caption = #1057#1090#1086#1080#1084#1086#1089#1090#1100' 1'#1085'/'#1095', '#1088#1091#1073
        TabOrder = 1
      end
    end
  end
end
