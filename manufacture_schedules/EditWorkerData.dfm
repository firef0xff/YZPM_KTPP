object WorkerData: TWorkerData
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = #1044#1072#1085#1085#1099#1077' '#1088#1072#1073#1086#1095#1077#1075#1086
  ClientHeight = 127
  ClientWidth = 390
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    390
    127)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 83
    Width = 36
    Height = 13
    Caption = #1043#1088#1091#1087#1087#1072
  end
  object ok: TBitBtn
    Left = 226
    Top = 94
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 0
    ExplicitTop = 85
  end
  object cancel: TBitBtn
    Left = 307
    Top = 94
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 1
    ExplicitTop = 85
  end
  object tab_no: TLabeledEdit
    Left = 8
    Top = 16
    Width = 49
    Height = 21
    EditLabel.Width = 34
    EditLabel.Height = 13
    EditLabel.Caption = #1058#1072#1073' '#8470
    NumbersOnly = True
    TabOrder = 2
  end
  object worker_family: TLabeledEdit
    Left = 8
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 44
    EditLabel.Height = 13
    EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103
    TabOrder = 3
  end
  object worker_name: TLabeledEdit
    Left = 135
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 19
    EditLabel.Height = 13
    EditLabel.Caption = #1048#1084#1103
    TabOrder = 4
  end
  object worker_otch: TLabeledEdit
    Left = 262
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 49
    EditLabel.Height = 13
    EditLabel.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
    TabOrder = 5
  end
  object razr: TLabeledEdit
    Left = 63
    Top = 16
    Width = 50
    Height = 21
    EditLabel.Width = 36
    EditLabel.Height = 13
    EditLabel.Caption = #1056#1072#1079#1088#1103#1076
    NumbersOnly = True
    TabOrder = 6
  end
  object proff: TLabeledEdit
    Left = 119
    Top = 16
    Width = 264
    Height = 21
    EditLabel.Width = 55
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1088#1086#1092#1077#1089#1089#1080#1103
    TabOrder = 7
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 97
    Width = 212
    Height = 21
    TabOrder = 8
    OnClick = ComboBox1Click
  end
end
