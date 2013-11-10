object instr: Tinstr
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = #1042#1099#1073#1086#1088' '#1080#1085#1089#1090#1088#1091#1084#1077#1085#1090#1072
  ClientHeight = 404
  ClientWidth = 586
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 209
    Top = 89
    Height = 315
    ExplicitLeft = 256
    ExplicitTop = 232
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 586
    Height = 89
    Align = alTop
    TabOrder = 0
    object LE1: TLabeledEdit
      Left = 8
      Top = 16
      Width = 404
      Height = 21
      EditLabel.Width = 20
      EditLabel.Height = 13
      EditLabel.Caption = #1050#1086#1076
      TabOrder = 0
    end
    object LE2: TLabeledEdit
      Left = 8
      Top = 56
      Width = 566
      Height = 21
      EditLabel.Width = 67
      EditLabel.Height = 13
      EditLabel.Caption = #1054#1073#1086#1079#1085#1072#1095#1077#1085#1080#1077
      TabOrder = 1
    end
    object BitBtn1: TBitBtn
      Left = 499
      Top = 14
      Width = 75
      Height = 25
      Caption = #1055#1088#1080#1085#1103#1090#1100
      DoubleBuffered = True
      Kind = bkOK
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 2
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      Left = 418
      Top = 14
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1072
      DoubleBuffered = True
      Kind = bkCancel
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 3
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 89
    Width = 209
    Height = 315
    Align = alLeft
    TabOrder = 1
    object TV: TTreeView
      Left = 1
      Top = 1
      Width = 207
      Height = 313
      Align = alClient
      Indent = 19
      ReadOnly = True
      TabOrder = 0
      OnDblClick = TVDblClick
      OnExpanding = TVExpanding
    end
  end
  object Panel3: TPanel
    Left = 212
    Top = 89
    Width = 374
    Height = 315
    Align = alClient
    TabOrder = 2
    object StringGrid1: TStringGrid
      Left = 1
      Top = 1
      Width = 372
      Height = 313
      Align = alClient
      ColCount = 3
      DefaultColWidth = 16
      DefaultRowHeight = 16
      Enabled = False
      FixedCols = 0
      RowCount = 2
      TabOrder = 0
    end
  end
end
