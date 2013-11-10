object zagotovka: Tzagotovka
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = #1047#1072#1075#1086#1090#1086#1074#1082#1080
  ClientHeight = 382
  ClientWidth = 536
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
  object Panel2: TPanel
    Left = 376
    Top = 0
    Width = 160
    Height = 382
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 0
    object RG1: TRadioGroup
      Left = 6
      Top = 8
      Width = 147
      Height = 49
      Caption = #1043#1088#1099#1087#1087#1099' '#1079#1072#1075#1086#1090#1086#1074#1086#1082
      ItemIndex = 0
      Items.Strings = (
        #1055#1086' '#1082#1086#1076#1091
        #1055#1086' '#1087#1088#1080#1084#1077#1085#1077#1085#1080#1102)
      TabOrder = 0
      OnClick = RG1Click
    end
    object Panel4: TPanel
      Left = 0
      Top = 63
      Width = 160
      Height = 319
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        160
        319)
      object Label1: TLabel
        Left = 6
        Top = 35
        Width = 43
        Height = 13
        Caption = #1050#1086#1076' '#1079#1072#1075'.'
      end
      object Label2: TLabel
        Left = 6
        Top = 273
        Width = 77
        Height = 13
        Anchors = [akLeft, akBottom]
        Caption = #1052#1077#1090#1086#1076' '#1088#1072#1089#1095#1077#1090#1072
        ExplicitTop = 336
      end
      object BB1: TBitBtn
        Left = 6
        Top = 7
        Width = 107
        Height = 22
        Caption = #1042' '#1090#1077#1093#1085#1086#1083#1086#1075#1080#1102
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
        TabOrder = 0
        OnClick = BB1Click
      end
      object BitBtn1: TBitBtn
        Left = 78
        Top = 242
        Width = 75
        Height = 25
        Anchors = [akLeft, akBottom]
        Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 1
        OnClick = BitBtn1Click
      end
      object Button1: TButton
        Left = 55
        Top = 35
        Width = 98
        Height = 21
        Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1092#1086#1088#1084#1091#1083
        TabOrder = 2
        OnClick = Button1Click
      end
      object CB1: TComboBox
        Left = 6
        Top = 292
        Width = 145
        Height = 22
        Style = csOwnerDrawFixed
        Anchors = [akLeft, akBottom]
        TabOrder = 3
        OnClick = CB1Click
      end
      object E1: TEdit
        Left = 6
        Top = 54
        Width = 43
        Height = 21
        NumbersOnly = True
        ReadOnly = True
        TabOrder = 4
      end
      object mass: TLabeledEdit
        Left = 6
        Top = 96
        Width = 147
        Height = 21
        EditLabel.Width = 59
        EditLabel.Height = 13
        EditLabel.Caption = #1063#1077#1088#1085#1099#1081' '#1074#1077#1089
        TabOrder = 5
      end
      object nrm: TLabeledEdit
        Left = 6
        Top = 137
        Width = 147
        Height = 21
        EditLabel.Width = 76
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1086#1088#1084#1072' '#1088#1072#1089#1093#1086#1076#1072
        TabOrder = 6
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 376
    Height = 382
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 0
      Top = 227
      Width = 376
      Height = 5
      Cursor = crVSplit
      Align = alBottom
      Color = clBtnFace
      ParentColor = False
      ExplicitTop = 229
    end
    object Panel3: TPanel
      Left = 0
      Top = 232
      Width = 376
      Height = 150
      Align = alBottom
      BevelEdges = [beTop]
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        376
        150)
      object SG1: TStringGrid
        Left = 0
        Top = 0
        Width = 376
        Height = 102
        Anchors = [akLeft, akTop, akRight, akBottom]
        ColCount = 3
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
        TabOrder = 0
      end
      object LE1: TLabeledEdit
        Left = 8
        Top = 123
        Width = 368
        Height = 21
        Anchors = [akLeft, akRight, akBottom]
        EditLabel.Width = 98
        EditLabel.Height = 13
        EditLabel.Caption = #1056#1072#1079#1084#1077#1088#1099' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
        TabOrder = 1
      end
    end
    object TV: TTreeView
      Left = 0
      Top = 0
      Width = 376
      Height = 227
      Align = alClient
      Indent = 19
      ReadOnly = True
      TabOrder = 1
      OnDblClick = TVDblClick
      OnExpanding = TVExpanding
    end
  end
end
