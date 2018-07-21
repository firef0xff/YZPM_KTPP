object FormAddZagCode: TFormAddZagCode
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1082#1086#1076#1072' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
  ClientHeight = 138
  ClientWidth = 195
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 8
    Top = 56
    Width = 61
    Height = 13
    Caption = #1055#1088#1080#1084#1077#1085#1077#1085#1080#1077
  end
  object eCode: TLabeledEdit
    Left = 8
    Top = 25
    Width = 61
    Height = 21
    EditLabel.Width = 20
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1076
    TabOrder = 0
  end
  object bOk: TBitBtn
    Left = 8
    Top = 103
    Width = 82
    Height = 23
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 1
    OnClick = bOkClick
  end
  object bCancel: TBitBtn
    Left = 103
    Top = 103
    Width = 82
    Height = 23
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 2
  end
  object cbUse: TComboBox
    Left = 8
    Top = 72
    Width = 177
    Height = 22
    Style = csOwnerDrawVariable
    TabOrder = 3
  end
  object eName: TLabeledEdit
    Left = 75
    Top = 25
    Width = 110
    Height = 21
    EditLabel.Width = 48
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077
    TabOrder = 4
  end
end
