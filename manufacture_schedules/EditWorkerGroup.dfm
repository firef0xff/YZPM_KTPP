object WorkerGroup: TWorkerGroup
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1043#1088#1091#1087#1087#1072' '#1088#1072#1073#1086#1095#1080#1093
  ClientHeight = 91
  ClientWidth = 301
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  DesignSize = (
    301
    91)
  PixelsPerInch = 96
  TextHeight = 13
  object group_name: TLabeledEdit
    Left = 8
    Top = 24
    Width = 285
    Height = 21
    EditLabel.Width = 36
    EditLabel.Height = 13
    EditLabel.Caption = #1043#1088#1091#1087#1087#1072
    TabOrder = 0
  end
  object r_kol: TLabeledEdit
    Left = 8
    Top = 64
    Width = 121
    Height = 21
    EditLabel.Width = 115
    EditLabel.Height = 13
    EditLabel.Caption = #1056#1072#1089#1095#1077#1090#1085#1086#1077' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086
    NumbersOnly = True
    TabOrder = 1
  end
  object ok: TBitBtn
    Left = 137
    Top = 62
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 2
  end
  object cancel: TBitBtn
    Left = 218
    Top = 62
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 3
  end
end
