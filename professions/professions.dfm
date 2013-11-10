object Professinos: TProfessinos
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = #1057#1087#1088#1072#1074#1086#1095#1085#1080#1082' '#1087#1088#1086#1092#1077#1089#1089#1080#1081
  ClientHeight = 307
  ClientWidth = 565
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
  object Splitter1: TSplitter
    Left = 286
    Top = 0
    Width = 5
    Height = 274
    Align = alRight
    ExplicitLeft = 285
    ExplicitTop = -6
  end
  object SG1: TStringGrid
    Left = 0
    Top = 0
    Width = 286
    Height = 274
    Align = alClient
    ColCount = 3
    DefaultColWidth = 16
    DefaultRowHeight = 16
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 0
    ExplicitWidth = 267
  end
  object Panel2: TPanel
    Left = 0
    Top = 274
    Width = 565
    Height = 33
    Align = alBottom
    TabOrder = 1
    ExplicitWidth = 522
    DesignSize = (
      565
      33)
    object cancel: TBitBtn
      Left = 484
      Top = 4
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1054#1090#1084#1077#1085#1072
      DoubleBuffered = True
      Kind = bkCancel
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 0
      ExplicitLeft = 441
    end
    object CB: TComboBox
      Left = 5
      Top = 7
      Width = 177
      Height = 22
      Style = csOwnerDrawVariable
      Anchors = [akLeft, akBottom]
      ItemIndex = 1
      TabOrder = 1
      Text = #1042#1089#1077
      OnClick = CBClick
      Items.Strings = (
        #1048#1089#1087#1086#1083#1100#1079#1091#1077#1084#1099#1077' '#1074' '#1090#1077#1093#1085#1086#1083#1086#1075#1080#1103#1093
        #1042#1089#1077)
    end
    object ok: TBitBtn
      Left = 403
      Top = 4
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1055#1088#1080#1085#1103#1090#1100
      DoubleBuffered = True
      Kind = bkOK
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 2
      OnClick = okClick
      ExplicitLeft = 360
    end
  end
  object SG2: TStringGrid
    Left = 291
    Top = 0
    Width = 274
    Height = 274
    Align = alRight
    ColCount = 4
    DefaultColWidth = 16
    DefaultRowHeight = 16
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 2
    OnSelectCell = SG2SelectCell
    ExplicitLeft = 248
  end
end
