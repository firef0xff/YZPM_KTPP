object komplekt: Tkomplekt
  Left = 0
  Top = 0
  Caption = #1050#1086#1084#1087#1083#1077#1082#1090
  ClientHeight = 171
  ClientWidth = 278
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    278
    171)
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 262
    Height = 129
    Anchors = [akLeft, akTop, akRight]
    Caption = #1042#1077#1076#1086#1084#1086#1089#1090#1080
    TabOrder = 0
    DesignSize = (
      262
      129)
    object materials: TCheckBox
      Left = 3
      Top = 16
      Width = 248
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      Caption = #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1084#1072#1090#1077#1088#1080#1072#1083#1086#1074
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object litho: TCheckBox
      Left = 3
      Top = 39
      Width = 248
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      Caption = #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1083#1080#1090#1100#1103
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
    object forging: TCheckBox
      Left = 3
      Top = 62
      Width = 248
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      Caption = #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1087#1086#1082#1086#1074#1086#1082
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
    object cooperation: TCheckBox
      Left = 3
      Top = 108
      Width = 248
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      Caption = #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1087#1086' '#1082#1086#1086#1087#1077#1088#1072#1094#1080#1080
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object shtamping: TCheckBox
      Left = 3
      Top = 85
      Width = 248
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      Caption = #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1096#1090#1072#1084#1087#1086#1074#1072#1085#1085#1099#1093' '#1076#1077#1090#1072#1083#1077#1081
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
  end
  object BitBtn1: TBitBtn
    Left = 163
    Top = 143
    Width = 107
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1060#1086#1088#1084#1080#1088#1086#1074#1072#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 1
  end
  object BitBtn2: TBitBtn
    Left = 82
    Top = 143
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 2
  end
end
