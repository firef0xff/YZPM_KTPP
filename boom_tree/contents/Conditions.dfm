object Cond: TCond
  Left = 0
  Top = 0
  Caption = #1048#1079#1084#1077#1085#1077#1085#1080#1077' '#1090#1077#1082#1091#1097#1077#1075#1086' '#1089#1090#1086#1089#1090#1086#1103#1085#1080#1103
  ClientHeight = 304
  ClientWidth = 489
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 318
    Top = 0
    Width = 171
    Height = 304
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      171
      304)
    object CondName: TLabel
      Left = 36
      Top = 242
      Width = 103
      Height = 13
      Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1089#1086#1089#1090#1086#1103#1085#1080#1103
    end
    object IMG: TImage
      Left = 6
      Top = 231
      Width = 24
      Height = 24
    end
    object prev: TButton
      Left = 38
      Top = 71
      Width = 91
      Height = 25
      Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1077#1077
      TabOrder = 0
      OnClick = prevClick
    end
    object next: TButton
      Left = 38
      Top = 9
      Width = 91
      Height = 25
      Caption = #1057#1083#1077#1076#1091#1102#1097#1077#1077
      TabOrder = 1
      OnClick = nextClick
    end
    object current: TButton
      Left = 38
      Top = 40
      Width = 91
      Height = 25
      Caption = #1048#1089#1093#1086#1076#1085#1086#1077
      TabOrder = 2
      OnClick = currentClick
    end
    object RG1: TRadioGroup
      Left = 6
      Top = 102
      Width = 147
      Height = 51
      Caption = #1060#1080#1083#1100#1090#1088#1072#1094#1080#1103' '#1087#1086' '#1089#1086#1089#1090#1086#1103#1085#1080#1102
      ItemIndex = 0
      Items.Strings = (
        #1042#1089#1077
        #1042#1099#1073#1088#1072#1085#1085#1099#1077)
      TabOrder = 3
    end
    object RG2: TRadioGroup
      Left = 6
      Top = 159
      Width = 147
      Height = 66
      Caption = #1060#1080#1083#1100#1090#1088#1072#1094#1080#1103' '#1087#1086' '#1076#1077#1090#1072#1083#1103#1084
      ItemIndex = 0
      Items.Strings = (
        #1042#1089#1077
        #1050#1088#1086#1084#1077' '#1089#1090#1072#1085#1076#1072#1088#1090#1085#1099#1093
        #1058#1086#1083#1100#1082#1086' '#1086#1088#1080#1075#1080#1085#1072#1083#1100#1085#1099#1077)
      TabOrder = 4
    end
    object BitBtn3: TBitBtn
      Left = 7
      Top = 266
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1055#1088#1080#1085#1103#1090#1100
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
      ModalResult = 1
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 5
      OnClick = BitBtn3Click
    end
    object BitBtn4: TBitBtn
      Left = 88
      Top = 266
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1054#1090#1084#1077#1085#1072
      DoubleBuffered = True
      Kind = bkCancel
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 6
    end
  end
  object TV: TTreeView
    Left = 0
    Top = 0
    Width = 318
    Height = 304
    Align = alClient
    Indent = 27
    MultiSelect = True
    MultiSelectStyle = [msControlSelect, msShiftSelect]
    ReadOnly = True
    RightClickSelect = True
    ShowButtons = False
    ShowLines = False
    ShowRoot = False
    TabOrder = 1
    OnClick = TVClick
    OnMouseDown = TVMouseDown
  end
end
