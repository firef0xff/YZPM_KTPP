object Obd_edit: TObd_edit
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1042#1074#1077#1076#1080#1090#1077' '#1086#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077
  ClientHeight = 84
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
    84)
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
    Left = 8
    Top = 16
    Width = 264
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 0
  end
  object BitBtn2: TBitBtn
    Left = 116
    Top = 51
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 1
  end
  object BitBtn1: TBitBtn
    Left = 197
    Top = 51
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
