object Form3: TForm3
  Left = 0
  Top = 0
  Caption = #1050#1086#1085#1074#1077#1088#1090#1086#1088' '#1089#1087#1077#1094#1080#1092#1080#1082#1072#1094#1080#1081' '#1050#1086#1084#1087#1072#1089
  ClientHeight = 175
  ClientWidth = 443
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 143
    Top = 8
    Width = 129
    Height = 25
    Caption = #1086#1090#1082#1088#1099#1090#1100' '#1089#1087#1077#1094#1080#1092#1080#1082#1072#1094#1080#1102
    TabOrder = 0
    OnClick = Button1Click
  end
  object LE1: TLabeledEdit
    Left = 8
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 117
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1077#1088#1074#1072#1103' '#1089#1090#1088#1086#1082#1072' '#1076#1072#1085#1085#1099#1093
    NumbersOnly = True
    TabOrder = 1
  end
  object LE2: TLabeledEdit
    Left = 135
    Top = 56
    Width = 121
    Height = 21
    EditLabel.Width = 134
    EditLabel.Height = 13
    EditLabel.Caption = #1087#1086#1089#1083#1077#1076#1085#1103#1103' '#1089#1090#1088#1086#1082#1072' '#1076#1072#1085#1085#1099#1093
    NumbersOnly = True
    TabOrder = 2
  end
  object Button2: TButton
    Left = 8
    Top = 123
    Width = 177
    Height = 25
    Caption = #1050#1086#1085#1074#1077#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1089#1087#1077#1094#1080#1092#1080#1082#1072#1094#1080#1102
    Enabled = False
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 8
    Width = 129
    Height = 25
    Caption = #1059#1082#1072#1079#1072#1090#1100' '#1096#1072#1073#1083#1086#1085
    TabOrder = 4
    OnClick = Button3Click
  end
  object SG: TStringGrid
    Left = 278
    Top = 8
    Width = 159
    Height = 159
    ColCount = 2
    DefaultColWidth = 70
    DefaultRowHeight = 16
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
    TabOrder = 5
    OnSetEditText = SGSetEditText
  end
  object LE: TLabeledEdit
    Left = 8
    Top = 96
    Width = 248
    Height = 21
    EditLabel.Width = 136
    EditLabel.Height = 13
    EditLabel.Caption = #1052#1072#1089#1082#1072' '#1088#1072#1089#1089#1090#1072#1085#1086#1074#1082#1080' '#1079#1085#1072#1082#1086#1074
    TabOrder = 6
    Text = '____.____.___.__-__'
  end
  object OD: TOpenDialog
    Filter = 'excel|*.xls; *.xlsx; *.xlt;'
    Left = 192
    Top = 120
  end
end
