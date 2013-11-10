object TrbOptions: TTrbOptions
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1086#1090#1095#1077#1090#1072
  ClientHeight = 219
  ClientWidth = 325
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
  object Label1: TLabel
    Left = 133
    Top = 163
    Width = 85
    Height = 13
    Caption = #1089#1090#1088#1072#1085#1080#1094' '#1085#1072' '#1092#1072#1081#1083
  end
  object OneRow: TCheckBox
    Left = 8
    Top = 8
    Width = 210
    Height = 17
    Caption = #1055#1077#1095#1072#1090#1072#1090#1100' '#1086#1076#1085#1086' '#1090#1088#1077#1073#1086#1072#1074#1085#1080#1077' '#1085#1072' '#1073#1083#1072#1085#1082
    Checked = True
    State = cbChecked
    TabOrder = 0
  end
  object FileName: TLabeledEdit
    Left = 6
    Top = 126
    Width = 265
    Height = 21
    EditLabel.Width = 80
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082':'
    TabOrder = 1
  end
  object SetFile: TButton
    Left = 277
    Top = 125
    Width = 40
    Height = 25
    Caption = '...'
    TabOrder = 2
    OnClick = SetFileClick
  end
  object ActiveDelimiter: TCheckBox
    Left = 6
    Top = 160
    Width = 89
    Height = 17
    Caption = #1056#1072#1079#1073#1080#1074#1072#1090#1100' '#1087#1086' '
    TabOrder = 3
  end
  object Count: TEdit
    Left = 94
    Top = 158
    Width = 33
    Height = 21
    NumbersOnly = True
    TabOrder = 4
    Text = '100'
  end
  object ok: TBitBtn
    Left = 161
    Top = 182
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 5
    OnClick = okClick
  end
  object cancel: TBitBtn
    Left = 242
    Top = 182
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 6
  end
  object Receiver: TLabeledEdit
    Left = 8
    Top = 88
    Width = 309
    Height = 21
    EditLabel.Width = 61
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1086#1083#1091#1095#1072#1090#1077#1083#1100
    TabOrder = 7
  end
  object Organization_: TLabeledEdit
    Left = 8
    Top = 48
    Width = 309
    Height = 21
    EditLabel.Width = 66
    EditLabel.Height = 13
    EditLabel.Caption = #1054#1088#1075#1072#1085#1080#1079#1072#1094#1080#1103
    TabOrder = 8
  end
  object SD: TSaveDialog
    Filter = 'Excel|*.xls; *.xlsx;'
    Left = 280
    Top = 16
  end
end
