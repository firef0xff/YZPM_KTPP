object Mater_add: TMater_add
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1044#1086#1073#1072#1074#1090#1100' '#1084#1072#1090#1077#1088#1080#1072#1083
  ClientHeight = 172
  ClientWidth = 330
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    330
    172)
  PixelsPerInch = 96
  TextHeight = 13
  object L1: TLabel
    Left = 8
    Top = 145
    Width = 110
    Height = 19
    Caption = #1054#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 8
    Top = 91
    Width = 101
    Height = 13
    Caption = #1045#1076#1080#1085#1080#1094#1099' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
  end
  object Label2: TLabel
    Left = 140
    Top = 91
    Width = 182
    Height = 13
    Caption = #1054#1090#1086#1073#1088#1072#1078#1072#1077#1084#1099#1077' '#1077#1076#1080#1085#1080#1094#1099' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
  end
  object LE1: TLabeledEdit
    Left = 8
    Top = 24
    Width = 186
    Height = 21
    EditLabel.Width = 73
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
    TabOrder = 0
  end
  object LE2: TLabeledEdit
    Left = 200
    Top = 24
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 23
    EditLabel.Height = 13
    EditLabel.Caption = #1043#1086#1089#1090
    TabOrder = 1
  end
  object LE3: TLabeledEdit
    Left = 8
    Top = 64
    Width = 186
    Height = 21
    EditLabel.Width = 45
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1088#1086#1092#1080#1083#1100
    TabOrder = 2
  end
  object LE4: TLabeledEdit
    Left = 200
    Top = 64
    Width = 121
    Height = 21
    Anchors = [akTop, akRight]
    EditLabel.Width = 85
    EditLabel.Height = 13
    EditLabel.Caption = #1043#1086#1089#1090' '#1085#1072' '#1087#1088#1086#1092#1080#1083#1100
    TabOrder = 3
  end
  object BitBtn1: TBitBtn
    Left = 152
    Top = 141
    Width = 82
    Height = 23
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 4
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 240
    Top = 141
    Width = 82
    Height = 23
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 5
  end
  object ei_opt: TComboBox
    Left = 140
    Top = 110
    Width = 182
    Height = 22
    Style = csOwnerDrawVariable
    ItemIndex = 0
    TabOrder = 6
    Text = #1048#1089#1087#1086#1083#1100#1079#1091#1077#1084#1099#1077' '#1085#1072' '#1089#1082#1083#1072#1076#1077
    OnClick = ei_optClick
    Items.Strings = (
      #1048#1089#1087#1086#1083#1100#1079#1091#1077#1084#1099#1077' '#1085#1072' '#1089#1082#1083#1072#1076#1077
      #1042#1089#1090#1088#1077#1095#1072#1102#1097#1080#1077#1089#1103' '#1074' '#1090#1077#1093#1085#1086#1083#1086#1075#1080#1103#1093
      #1055#1086#1083#1085#1099#1081' '#1089#1087#1080#1089#1086#1082)
  end
  object ei: TComboBox
    Left = 8
    Top = 110
    Width = 126
    Height = 21
    Style = csDropDownList
    TabOrder = 7
  end
end
