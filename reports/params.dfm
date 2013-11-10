object parametr: Tparametr
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1042#1074#1077#1076#1080#1090#1077' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
  ClientHeight = 116
  ClientWidth = 266
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object cex: TLabeledEdit
    Left = 8
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 58
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1086#1084#1077#1088' '#1094#1077#1093#1072
    MaxLength = 4
    NumbersOnly = True
    TabOrder = 0
  end
  object zak: TLabeledEdit
    Left = 135
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 68
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1086#1084#1077#1088' '#1079#1072#1082#1072#1079#1072
    MaxLength = 6
    NumbersOnly = True
    TabOrder = 1
  end
  object part: TLabeledEdit
    Left = 8
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 70
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1086#1084#1077#1088' '#1087#1072#1088#1090#1080#1080
    MaxLength = 2
    TabOrder = 2
  end
  object kol: TLabeledEdit
    Left = 135
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 100
    EditLabel.Height = 13
    EditLabel.Caption = #1056#1072#1079#1084#1077#1088' '#1087#1072#1088#1090#1080#1080', '#1076#1077#1090
    NumbersOnly = True
    TabOrder = 3
    Text = '1'
  end
  object BitBtn1: TBitBtn
    Left = 183
    Top = 83
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 4
  end
end
