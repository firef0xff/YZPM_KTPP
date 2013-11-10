object Fomul_Editor: TFomul_Editor
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1092#1086#1088#1084#1091#1083
  ClientHeight = 371
  ClientWidth = 428
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnActivate = FormActivate
  DesignSize = (
    428
    371)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 56
    Top = 0
    Width = 82
    Height = 13
    Caption = #1052#1077#1090#1086#1076' '#1088#1072#1089#1089#1095#1077#1090#1072
  end
  object Label2: TLabel
    Left = 8
    Top = 166
    Width = 112
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1080#1079' '#1092#1086#1088#1084#1091#1083
  end
  object Label3: TLabel
    Left = 216
    Top = 166
    Width = 121
    Height = 13
    Caption = #1043#1083#1086#1073#1072#1083#1100#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
  end
  object LE1: TLabeledEdit
    Left = 8
    Top = 16
    Width = 41
    Height = 21
    EditLabel.Width = 43
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1076' '#1079#1072#1075'.'
    NumbersOnly = True
    TabOrder = 0
    OnChange = LE1Change
  end
  object LE2: TLabeledEdit
    Left = 8
    Top = 56
    Width = 410
    Height = 21
    EditLabel.Width = 114
    EditLabel.Height = 13
    EditLabel.Caption = #1060#1086#1088#1084#1091#1083#1072' '#1095#1077#1088#1085#1086#1075#1086' '#1074#1077#1089#1072
    TabOrder = 1
    OnChange = LE2Change
  end
  object LE3: TLabeledEdit
    Left = 8
    Top = 96
    Width = 410
    Height = 21
    EditLabel.Width = 124
    EditLabel.Height = 13
    EditLabel.Caption = #1060#1086#1088#1084#1091#1083#1072' '#1085#1086#1088#1084#1099' '#1088#1072#1089#1093#1086#1076#1072
    TabOrder = 2
    OnChange = LE2Change
  end
  object CB1: TComboBox
    Left = 55
    Top = 16
    Width = 194
    Height = 21
    TabOrder = 3
    OnClick = CB1Click
  end
  object BitBtn1: TBitBtn
    Left = 320
    Top = 338
    Width = 98
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    Default = True
    DoubleBuffered = True
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 4
    OnClick = BitBtn1Click
  end
  object SG1: TStringGrid
    Left = 8
    Top = 185
    Width = 202
    Height = 149
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 3
    DefaultColWidth = 16
    DefaultRowHeight = 16
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
    TabOrder = 5
    OnSetEditText = SG1SetEditText
  end
  object LE4: TLabeledEdit
    Left = 8
    Top = 139
    Width = 410
    Height = 21
    EditLabel.Width = 90
    EditLabel.Height = 13
    EditLabel.Caption = #1056#1072#1079#1084#1077#1088' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
    TabOrder = 6
  end
  object SG0: TStringGrid
    Left = 216
    Top = 185
    Width = 204
    Height = 149
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 3
    DefaultColWidth = 16
    DefaultRowHeight = 16
    RowCount = 2
    TabOrder = 7
  end
  object BitBtn2: TBitBtn
    Left = 216
    Top = 338
    Width = 98
    Height = 25
    Cancel = True
    Caption = #1059#1076#1072#1083#1080#1090#1100
    DoubleBuffered = True
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333FFFFF333333000033333388888833333333333F888888FFF333
      000033338811111188333333338833FFF388FF33000033381119999111833333
      38F338888F338FF30000339119933331111833338F388333383338F300003391
      13333381111833338F8F3333833F38F3000039118333381119118338F38F3338
      33F8F38F000039183333811193918338F8F333833F838F8F0000391833381119
      33918338F8F33833F8338F8F000039183381119333918338F8F3833F83338F8F
      000039183811193333918338F8F833F83333838F000039118111933339118338
      F3833F83333833830000339111193333391833338F33F8333FF838F300003391
      11833338111833338F338FFFF883F83300003339111888811183333338FF3888
      83FF83330000333399111111993333333388FFFFFF8833330000333333999999
      3333333333338888883333330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 8
    OnClick = BitBtn2Click
  end
  object LE5: TLabeledEdit
    Left = 344
    Top = 16
    Width = 76
    Height = 21
    EditLabel.Width = 76
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082
    NumbersOnly = True
    TabOrder = 9
  end
end
