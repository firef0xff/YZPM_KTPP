object materials: Tmaterials
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = #1042#1099#1073#1086#1088' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
  ClientHeight = 464
  ClientWidth = 896
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 301
    Width = 896
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 0
    ExplicitWidth = 256
  end
  object Panel1: TPanel
    Left = 692
    Top = 0
    Width = 204
    Height = 301
    Align = alRight
    TabOrder = 0
    object next: TSpeedButton
      Left = 151
      Top = 142
      Width = 24
      Height = 22
      AllowAllUp = True
      Flat = True
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        18000000000068020000C40E0000C40E00000000000000000001EDE9EBEDE9EB
        EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9
        EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB393939EDE9
        EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9
        EBEDE9EBEDE9EB313131292929EDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9
        EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB292929292929292929EDE9EBED
        E9EBEDE9EBEDE9EB0000EDE9EB52525242424239393931313131313131313131
        3131292929292929292929EDE9EBEDE9EBEDE9EB0000EDE9EB5A5A5A5252524A
        4A4A4A4A4A424242424242424242393939313131292929292929EDE9EBEDE9EB
        0000EDE9EB6B6B6B6B6B6B6B6B6B6363636363635A5A5A5A5A5A525252424242
        393939393939393939EDE9EB0000EDE9EB7B7B7B7B7B7B7B7B7B7B7B7B737373
        7373736B6B6B6363635A5A5A5252524A4A4A4A4A4AEDE9EB0000EDE9EB848484
        8484848484848484848484848484847B7B7B7373736B6B6B6363635A5A5AEDE9
        EBEDE9EB0000EDE9EB8C8C8C8C8C8C8C8C8C8C8C8C8C8C8C8C8C8C8484847B7B
        7B7373736B6B6BEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9
        EBEDE9EBEDE9EB8484847B7B7B737373EDE9EBEDE9EBEDE9EBEDE9EB0000EDE9
        EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB8484847B7B7BEDE9EBEDE9EBED
        E9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB84
        8484EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBED
        E9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB
        0000}
      OnClick = nextClick
    end
    object prev: TSpeedButton
      Left = 87
      Top = 142
      Width = 24
      Height = 22
      Flat = True
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        18000000000068020000C40E0000C40E00000000000000000001EDE9EBEDE9EB
        EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9
        EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB313131EDE9EBEDE9
        EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9
        EB313131292929EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9
        EBEDE9EBEDE9EBEDE9EB393939313131292929EDE9EBEDE9EBEDE9EBEDE9EBED
        E9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EB4A4A4A42424239393931313129
        2929292929292929292929292929292929EDE9EB0000EDE9EBEDE9EB6363635A
        5A5A5252524A4A4A424242393939393939313131292929292929313131EDE9EB
        0000EDE9EB6B6B6B6B6B6B6B6B6B6B6B6B6363635A5A5A5252525252524A4A4A
        424242424242393939EDE9EB0000EDE9EB7B7B7B7B7B7B7B7B7B7B7B7B737373
        6B6B6B6B6B6B6B6B6B6363635A5A5A5252524A4A4AEDE9EB0000EDE9EBEDE9EB
        8484848484848484848484847B7B7B7B7B7B7373737373736B6B6B6363635A5A
        5AEDE9EB0000EDE9EBEDE9EBEDE9EB8C8C8C8C8C8C8C8C8C8484848484847B7B
        7B7B7B7B7373737373736B6B6BEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EB8C8C
        8C8C8C8C848484EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9
        EBEDE9EBEDE9EBEDE9EBEDE9EB8C8C8C848484EDE9EBEDE9EBEDE9EBEDE9EBED
        E9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB848484ED
        E9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBED
        E9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB
        0000}
      OnClick = prevClick
    end
    object RG: TRadioGroup
      Left = 6
      Top = 170
      Width = 195
      Height = 69
      Caption = #1056#1077#1078#1080#1084' '#1089#1086#1088#1090#1080#1088#1086#1074#1082#1080
      ItemIndex = 0
      Items.Strings = (
        #1055#1086' '#1086#1073#1086#1079#1085#1072#1095#1077#1085#1080#1102
        #1055#1086' '#1087#1088#1086#1092#1080#1083#1102', '#1087#1086' '#1084#1072#1088#1082#1077
        #1055#1086' '#1084#1072#1088#1082#1077', '#1087#1086' '#1087#1088#1086#1092#1080#1083#1102
        #1055#1086' '#1043#1054#1057#1058' '#1085#1072' '#1087#1088#1086#1092#1080#1083#1100)
      TabOrder = 0
      OnClick = RGClick
    end
    object LE1: TLabeledEdit
      Left = 6
      Top = 24
      Width = 83
      Height = 21
      EditLabel.Width = 124
      EditLabel.Height = 13
      EditLabel.Caption = #1054#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077' '#1089#1086#1076#1077#1088#1078#1080#1090':'
      MaxLength = 6
      TabOrder = 1
    end
    object LE2: TLabeledEdit
      Left = 6
      Top = 64
      Width = 163
      Height = 21
      EditLabel.Width = 130
      EditLabel.Height = 13
      EditLabel.Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1089#1086#1076#1077#1088#1078#1080#1090':'
      TabOrder = 2
    end
    object LE3: TLabeledEdit
      Left = 6
      Top = 104
      Width = 163
      Height = 21
      EditLabel.Width = 102
      EditLabel.Height = 13
      EditLabel.Caption = #1055#1088#1086#1092#1080#1083#1100' '#1089#1086#1076#1077#1088#1078#1080#1090':'
      TabOrder = 3
    end
    object Button1: TButton
      Left = 95
      Top = 22
      Width = 75
      Height = 25
      Caption = #1048#1089#1082#1072#1090#1100
      TabOrder = 4
      OnClick = Button1Click
    end
    object E2: TEdit
      Left = 117
      Top = 143
      Width = 28
      Height = 21
      NumbersOnly = True
      TabOrder = 5
      Text = '1'
      OnChange = E2Change
    end
    object E3: TLabeledEdit
      Left = 6
      Top = 143
      Width = 75
      Height = 21
      EditLabel.Width = 78
      EditLabel.Height = 13
      EditLabel.Caption = #1057#1090#1088#1086#1082' '#1085#1072' '#1083#1080#1089#1090#1077
      NumbersOnly = True
      TabOrder = 6
      Text = '20'
      OnChange = E3Change
    end
    object BB1: TBitBtn
      Left = 6
      Top = 245
      Width = 107
      Height = 22
      Caption = #1042' '#1090#1077#1093#1085#1086#1083#1086#1075#1080#1102
      DoubleBuffered = True
      Kind = bkOK
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 7
      OnClick = BB1Click
    end
    object Add: TButton
      Left = 6
      Top = 273
      Width = 91
      Height = 22
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 8
      OnClick = AddClick
    end
    object Del: TButton
      Left = 103
      Top = 273
      Width = 91
      Height = 22
      Caption = #1059#1076#1072#1083#1080#1090#1100
      TabOrder = 9
      OnClick = DelClick
    end
    object Button2: TButton
      Left = 119
      Top = 245
      Width = 75
      Height = 22
      Caption = #1047#1072#1084#1077#1085#1072
      TabOrder = 10
      OnClick = Button2Click
    end
  end
  object SG: TStringGrid
    Left = 0
    Top = 304
    Width = 896
    Height = 160
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 7
    DefaultColWidth = 16
    DefaultRowHeight = 16
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing, goAlwaysShowEditor]
    TabOrder = 1
  end
  object TV: TTreeView
    Left = 0
    Top = 0
    Width = 692
    Height = 301
    Align = alClient
    Indent = 19
    PopupMenu = PAB
    ReadOnly = True
    TabOrder = 2
    OnClick = TVClick
    OnExpanding = TVExpanding
  end
  object PAB: TPopupActionBar
    Left = 120
    Top = 72
    object N1: TMenuItem
      Caption = #1056#1072#1089#1082#1088#1099#1090#1100' '#1074#1089#1077
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1057#1074#1077#1088#1085#1091#1090#1100' '#1074#1089#1077
      OnClick = N2Click
    end
  end
end
