object wndEntarseMaterial: TwndEntarseMaterial
  Left = 309
  Top = 419
  Caption = #1055#1086#1089#1090#1091#1087#1083#1077#1085#1080#1077' '#1085#1072' '#1089#1082#1083#1072#1076
  ClientHeight = 176
  ClientWidth = 698
  Color = clBtnFace
  Constraints.MaxHeight = 206
  Constraints.MinHeight = 206
  Constraints.MinWidth = 649
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  DesignSize = (
    698
    176)
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 698
    Height = 137
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object pnGeometry: TPanel
      Left = 369
      Top = 0
      Width = 329
      Height = 137
      Align = alRight
      BevelKind = bkTile
      BevelOuter = bvNone
      TabOrder = 0
      object sgGeometry: TStringGrid
        Left = 0
        Top = 19
        Width = 325
        Height = 114
        Align = alClient
        BorderStyle = bsNone
        DefaultColWidth = 16
        DefaultRowHeight = 16
        RowCount = 2
        TabOrder = 0
        OnDblClick = sgGeometryDblClick
        OnSelectCell = sgGeometrySelectCell
        OnSetEditText = sgGeometrySetEditText
      end
      object lblsgGeometry: TPanel
        Left = 0
        Top = 0
        Width = 325
        Height = 19
        Align = alTop
        Caption = #1054#1087#1080#1089#1072#1085#1080#1077' '#1075#1077#1086#1084#1077#1090#1088#1080#1080
        TabOrder = 1
      end
      object cbGeometry: TComboBox
        Left = 88
        Top = 81
        Width = 97
        Height = 21
        Style = csDropDownList
        TabOrder = 2
        Visible = False
        OnClick = cbGeometryClick
        OnExit = cbGeometryExit
      end
    end
    object pnProp: TPanel
      Left = 0
      Top = 0
      Width = 369
      Height = 137
      Align = alClient
      BevelEdges = [beLeft, beTop, beRight]
      BevelOuter = bvNone
      Constraints.MaxHeight = 137
      Constraints.MinHeight = 137
      Constraints.MinWidth = 369
      TabOrder = 1
      DesignSize = (
        369
        137)
      object Label1: TLabel
        Left = 8
        Top = 86
        Width = 86
        Height = 13
        Caption = #1058#1080#1087' '#1087#1086#1089#1090#1091#1087#1083#1077#1085#1080#1103
      end
      object Label2: TLabel
        Left = 304
        Top = 89
        Width = 14
        Height = 13
        Anchors = [akTop, akRight]
        Caption = #1054#1090
        ExplicitLeft = 379
      end
      object Label3: TLabel
        Left = 305
        Top = 43
        Width = 42
        Height = 13
        Caption = #1045#1076'. '#1048#1079#1084'.'
      end
      object leName: TLabeledEdit
        Left = 8
        Top = 59
        Width = 290
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 73
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1072#1080#1084#1077#1085#1080#1074#1072#1085#1080#1077
        ReadOnly = True
        TabOrder = 0
      end
      object LabeledEdit2: TLabeledEdit
        Left = 240
        Top = 21
        Width = 58
        Height = 21
        Anchors = [akTop, akRight]
        EditLabel.Width = 30
        EditLabel.Height = 13
        EditLabel.Caption = #1052#1072#1089#1089#1072
        TabOrder = 1
      end
      object leObe: TLabeledEdit
        Left = 8
        Top = 21
        Width = 227
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 67
        EditLabel.Height = 13
        EditLabel.Caption = #1054#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077
        TabOrder = 2
        OnKeyDown = leObeKeyDown
      end
      object cbReason: TComboBox
        Left = 8
        Top = 105
        Width = 161
        Height = 21
        Style = csDropDownList
        ItemIndex = 0
        TabOrder = 3
        Text = #1055#1086#1087#1086#1083#1085#1077#1085#1080#1077' '#1089#1082#1083#1072#1076#1072
        Items.Strings = (
          #1055#1086#1087#1086#1083#1085#1077#1085#1080#1077' '#1089#1082#1083#1072#1076#1072
          #1042#1086#1079#1074#1088#1072#1090' '#1086#1089#1090#1072#1090#1082#1086#1074' '#1085#1072' '#1089#1082#1083#1072#1076)
      end
      object LabeledEdit6: TLabeledEdit
        Left = 177
        Top = 105
        Width = 40
        Height = 21
        BevelEdges = [beLeft, beTop, beBottom]
        EditLabel.Width = 26
        EditLabel.Height = 13
        EditLabel.Caption = #1062#1077#1085#1072
        TabOrder = 4
      end
      object LabeledEdit7: TLabeledEdit
        Left = 225
        Top = 105
        Width = 73
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        EditLabel.Width = 72
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1072#1082#1083#1072#1076#1085#1072#1103' '#8470
        TabOrder = 5
      end
      object MaskEdit1: TMaskEdit
        Left = 304
        Top = 105
        Width = 58
        Height = 21
        Anchors = [akTop, akRight]
        BevelEdges = [beTop, beRight, beBottom]
        EditMask = '!99/99/00;0;_'
        MaxLength = 8
        TabOrder = 6
      end
      object LabeledEdit3: TLabeledEdit
        Left = 304
        Top = 21
        Width = 58
        Height = 21
        Anchors = [akTop, akRight]
        EditLabel.Width = 35
        EditLabel.Height = 13
        EditLabel.Caption = #1050#1086#1083'-'#1074#1086
        TabOrder = 7
      end
      object cbEi: TComboBox
        Left = 305
        Top = 59
        Width = 58
        Height = 21
        ItemIndex = 0
        TabOrder = 8
        Text = #1055#1086#1087#1086#1083#1085#1077#1085#1080#1077' '#1089#1082#1083#1072#1076#1072
        Items.Strings = (
          #1055#1086#1087#1086#1083#1085#1077#1085#1080#1077' '#1089#1082#1083#1072#1076#1072
          #1042#1086#1079#1074#1088#1072#1090' '#1086#1089#1090#1072#1090#1082#1086#1074' '#1085#1072' '#1089#1082#1083#1072#1076)
      end
    end
  end
  object BitBtn1: TBitBtn
    Left = 615
    Top = 149
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 1
  end
  object BitBtn2: TBitBtn
    Left = 534
    Top = 149
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
    TabOrder = 2
  end
  object btContrAgent: TButton
    Left = 496
    Top = 149
    Width = 32
    Height = 25
    Anchors = [akTop, akRight]
    Caption = '...'
    TabOrder = 3
    OnClick = btContrAgentClick
  end
  object leContrAgent: TLabeledEdit
    Left = 8
    Top = 151
    Width = 482
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    EditLabel.Width = 57
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1086#1089#1090#1072#1074#1097#1080#1082
    TabOrder = 4
    OnDblClick = btContrAgentClick
  end
  object ADC: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Password=q23s10z56;Persist Security Info=True' +
      ';User ID=root;Data Source=yzpm;Initial Catalog=administration'
    Provider = 'MSDASQL.1'
    Left = 248
    Top = 200
  end
end
