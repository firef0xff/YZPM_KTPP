object PP_params: TPP_params
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1057#1086#1089#1090#1072#1074' '#1086#1090#1095#1077#1090#1072
  ClientHeight = 158
  ClientWidth = 327
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
    Left = 135
    Top = 108
    Width = 85
    Height = 13
    Caption = #1089#1090#1088#1072#1085#1080#1094' '#1085#1072' '#1092#1072#1081#1083
  end
  object P_pr: TCheckBox
    Left = 8
    Top = 8
    Width = 121
    Height = 17
    Caption = #1055#1083#1072#1085' '#1087#1088#1086#1080#1079#1074#1086#1076#1089#1090#1074#1072
    Checked = True
    State = cbChecked
    TabOrder = 0
    OnClick = P_prClick
  end
  object T_cex: TCheckBox
    Left = 135
    Top = 31
    Width = 138
    Height = 17
    Caption = #1058#1088#1091#1076#1086#1077#1084#1082#1086#1089#1090#1100' '#1087#1086' '#1094#1077#1093#1072#1084
    Checked = True
    State = cbChecked
    TabOrder = 1
  end
  object T_obor: TCheckBox
    Left = 135
    Top = 8
    Width = 183
    Height = 17
    Caption = #1058#1088#1091#1076#1086#1077#1084#1082#1086#1089#1090#1100' '#1087#1086' '#1086#1073#1086#1088#1091#1076#1086#1074#1072#1085#1080#1102
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object cancel: TBitBtn
    Left = 244
    Top = 127
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    DoubleBuffered = True
    Kind = bkCancel
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 3
  end
  object ok: TBitBtn
    Left = 163
    Top = 127
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    DoubleBuffered = True
    Kind = bkOK
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 4
    OnClick = okClick
  end
  object ML: TCheckBox
    Left = 8
    Top = 31
    Width = 121
    Height = 17
    Caption = #1052#1072#1088#1096#1088#1091#1090#1085#1099#1077' '#1083#1080#1089#1090#1099
    Checked = True
    State = cbChecked
    TabOrder = 5
  end
  object FileName: TLabeledEdit
    Left = 8
    Top = 71
    Width = 265
    Height = 21
    EditLabel.Width = 80
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082':'
    TabOrder = 6
  end
  object SetFile: TButton
    Left = 279
    Top = 70
    Width = 40
    Height = 25
    Caption = '...'
    TabOrder = 7
    OnClick = SetFileClick
  end
  object ActiveDelimiter: TCheckBox
    Left = 8
    Top = 105
    Width = 89
    Height = 17
    Caption = #1056#1072#1079#1073#1080#1074#1072#1090#1100' '#1087#1086' '
    TabOrder = 8
  end
  object Count: TEdit
    Left = 96
    Top = 103
    Width = 33
    Height = 21
    NumbersOnly = True
    TabOrder = 9
    Text = '100'
  end
  object SD: TSaveDialog
    Filter = 'Excel|*.xls; *.xlsx;'
    Left = 280
    Top = 24
  end
end
