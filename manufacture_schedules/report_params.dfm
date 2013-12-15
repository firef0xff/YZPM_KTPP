object RepParams: TRepParams
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1090#1095#1077#1090#1072
  ClientHeight = 328
  ClientWidth = 337
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
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 337
    Height = 73
    Align = alTop
    TabOrder = 0
    DesignSize = (
      337
      73)
    object Label1: TLabel
      Left = 135
      Top = 54
      Width = 85
      Height = 13
      Anchors = [akLeft, akBottom]
      Caption = #1089#1090#1088#1072#1085#1080#1094' '#1085#1072' '#1092#1072#1081#1083
    end
    object ActiveDelimiter: TCheckBox
      Left = 8
      Top = 50
      Width = 89
      Height = 17
      Anchors = [akLeft, akBottom]
      Caption = #1056#1072#1079#1073#1080#1074#1072#1090#1100' '#1087#1086' '
      TabOrder = 0
    end
    object Count: TEdit
      Left = 96
      Top = 46
      Width = 33
      Height = 21
      Anchors = [akLeft, akBottom]
      NumbersOnly = True
      TabOrder = 1
      Text = '100'
    end
    object FileName: TLabeledEdit
      Left = 8
      Top = 21
      Width = 265
      Height = 21
      Anchors = [akLeft, akBottom]
      EditLabel.Width = 80
      EditLabel.Height = 13
      EditLabel.Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082':'
      TabOrder = 2
      OnChange = FileNameChange
    end
    object SetFile: TButton
      Left = 279
      Top = 19
      Width = 40
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = '...'
      TabOrder = 3
      OnClick = SetFileClick
    end
  end
  object MidPanel: TPanel
    Left = 0
    Top = 73
    Width = 337
    Height = 221
    Align = alClient
    TabOrder = 1
    object OptionsSG: TStringGrid
      Left = 1
      Top = 1
      Width = 335
      Height = 219
      Align = alClient
      ColCount = 2
      DefaultColWidth = 16
      DefaultRowHeight = 16
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 294
    Width = 337
    Height = 34
    Align = alBottom
    TabOrder = 2
    DesignSize = (
      337
      34)
    object ok: TBitBtn
      Left = 173
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1088#1080#1085#1103#1090#1100
      DoubleBuffered = True
      Kind = bkOK
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 0
      OnClick = okClick
    end
    object cancel: TBitBtn
      Left = 254
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1054#1090#1084#1077#1085#1072
      DoubleBuffered = True
      Kind = bkCancel
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 1
    end
  end
  object SD: TSaveDialog
    Filter = 'Excel|*.xls; *.xlsx;'
    Left = 224
    Top = 8
  end
end
