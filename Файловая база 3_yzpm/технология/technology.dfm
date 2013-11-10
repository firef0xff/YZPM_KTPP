object TechWnd: TTechWnd
  Left = 0
  Top = 0
  Width = 847
  Height = 607
  TabOrder = 0
  object Splitter1: TSplitter
    Left = 0
    Top = 417
    Width = 847
    Height = 5
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 421
  end
  object Panel3: TPanel
    Left = 0
    Top = 422
    Width = 847
    Height = 185
    Align = alBottom
    BevelEdges = [beTop]
    BevelKind = bkTile
    BevelOuter = bvNone
    UseDockManager = False
    FullRepaint = False
    ParentBackground = False
    ShowCaption = False
    TabOrder = 0
    object Splitter3: TSplitter
      Left = 603
      Top = 0
      Width = 5
      Height = 183
      Align = alRight
      ExplicitLeft = 442
      ExplicitTop = 4
    end
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 603
      Height = 183
      Align = alClient
      BevelEdges = [beRight]
      BevelKind = bkTile
      BevelOuter = bvNone
      Constraints.MinHeight = 5
      Constraints.MinWidth = 5
      ShowCaption = False
      TabOrder = 0
      object perexod: TRichEdit
        Left = 0
        Top = 0
        Width = 601
        Height = 183
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Autoproject'
        Font.Style = []
        Constraints.MinHeight = 5
        Constraints.MinWidth = 5
        ParentFont = False
        PopupMenu = PAB2
        ScrollBars = ssVertical
        TabOrder = 0
        OnChange = perexodChange
        OnEnter = perexodEnter
        OnExit = perexodExit
      end
    end
    object Panel2: TPanel
      Left = 608
      Top = 0
      Width = 239
      Height = 183
      Align = alRight
      BevelEdges = [beLeft]
      BevelKind = bkTile
      BevelOuter = bvNone
      Constraints.MinHeight = 5
      Constraints.MinWidth = 5
      ShowCaption = False
      TabOrder = 1
      object instrum: TStringGrid
        Left = 0
        Top = 0
        Width = 237
        Height = 183
        Align = alClient
        BevelEdges = [beRight]
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        ColCount = 3
        Constraints.MinHeight = 5
        Constraints.MinWidth = 5
        DefaultColWidth = 16
        DefaultRowHeight = 16
        RowCount = 2
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
        ParentFont = False
        TabOrder = 0
        OnDblClick = instrumDblClick
        OnExit = instrumExit
      end
    end
  end
  object operations: TStringGrid
    Left = 31
    Top = 121
    Width = 816
    Height = 296
    Align = alClient
    BevelInner = bvNone
    BevelOuter = bvNone
    BorderStyle = bsNone
    ColCount = 19
    Constraints.MinHeight = 5
    Constraints.MinWidth = 5
    DefaultColWidth = 16
    DefaultRowHeight = 16
    RowCount = 2
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowMoving]
    ParentFont = False
    PopupMenu = PAB
    TabOrder = 1
    OnDblClick = operationsDblClick
    OnDrawCell = operationsDrawCell
    OnKeyDown = operationsKeyDown
    OnRowMoved = operationsRowMoved
    OnSelectCell = operationsSelectCell
    OnSetEditText = operationsSetEditText
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 847
    Height = 121
    Align = alTop
    BevelEdges = [beBottom]
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 2
    object PageControl3: TPageControl
      Left = 0
      Top = 0
      Width = 847
      Height = 119
      ActivePage = Detailparam
      Align = alClient
      Images = ImageList1
      MultiLine = True
      Style = tsFlatButtons
      TabOrder = 0
      object Detailparam: TTabSheet
        Caption = #1054#1073#1097#1080#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
        ImageIndex = -1
        ParentShowHint = False
        ShowHint = True
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        DesignSize = (
          839
          87)
        object DT_Name: TLabel
          Left = 244
          Top = 43
          Width = 97
          Height = 16
          Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object creator: TLabel
          Left = 3
          Top = 71
          Width = 37
          Height = 13
          Caption = #1057#1086#1079#1076#1072#1083
        end
        object updater: TLabel
          Left = 244
          Top = 74
          Width = 73
          Height = 13
          Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1083
        end
        object access: TLabel
          Left = 548
          Top = 74
          Width = 37
          Height = 13
          Caption = #1044#1086#1089#1090#1091#1087
        end
        object napr: TLabeledEdit
          Left = 3
          Top = 16
          Width = 79
          Height = 21
          EditLabel.Width = 67
          EditLabel.Height = 13
          EditLabel.Caption = #1053#1072#1087#1088#1072#1074#1083#1077#1085#1080#1077
          MaxLength = 4
          NumbersOnly = True
          TabOrder = 0
          OnChange = naprChange
          OnExit = naprExit
        end
        object rasceh: TLabeledEdit
          Left = 88
          Top = 16
          Width = 748
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          EditLabel.Width = 59
          EditLabel.Height = 13
          EditLabel.Caption = #1056#1072#1089#1094#1077#1093#1086#1074#1082#1072
          ReadOnly = True
          TabOrder = 1
        end
        object Panel5: TPanel
          Left = 0
          Top = 43
          Width = 238
          Height = 25
          BevelEdges = []
          BevelOuter = bvNone
          TabOrder = 2
        end
      end
      object TabSheet9: TTabSheet
        Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1076#1077#1090#1072#1083#1080
        ImageIndex = -1
        ParentShowHint = False
        ShowHint = True
        ExplicitLeft = 8
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object L1: TLabel
          Left = 1
          Top = 56
          Width = 3
          Height = 13
        end
        object L2: TLabel
          Left = 135
          Top = 56
          Width = 3
          Height = 13
        end
        object L3: TLabel
          Left = 135
          Top = 43
          Width = 3
          Height = 13
        end
        object L4: TLabel
          Left = 135
          Top = 70
          Width = 3
          Height = 13
        end
        object Label1: TLabel
          Left = 254
          Top = 0
          Width = 41
          Height = 13
          Caption = #1045#1076'. '#1080#1079#1084'.'
        end
        object Label3: TLabel
          Left = 326
          Top = 0
          Width = 182
          Height = 13
          Caption = #1054#1090#1086#1073#1088#1072#1078#1072#1077#1084#1099#1077' '#1077#1076#1077#1085#1080#1094#1099' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
        end
        object masd: TLabeledEdit
          Left = 182
          Top = 16
          Width = 66
          Height = 21
          EditLabel.Width = 56
          EditLabel.Height = 13
          EditLabel.Caption = #1052#1072#1089#1089#1072' '#1076#1077#1090'.'
          TabOrder = 2
          OnChange = DoubleFildChange
          OnEnter = masdEnter
          OnExit = masdExit
        end
        object obm: TLabeledEdit
          Left = 3
          Top = 16
          Width = 173
          Height = 21
          EditLabel.Width = 105
          EditLabel.Height = 13
          EditLabel.Caption = #1052#1072#1090#1077#1088#1080#1072#1083' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
          TabOrder = 1
          OnChange = obmChange
          OnDblClick = obmDblClick
          OnExit = obmExit
        end
        object ei: TComboBox
          Left = 254
          Top = 16
          Width = 66
          Height = 21
          Style = csDropDownList
          TabOrder = 0
          OnClick = eiClick
        end
        object ei_opt: TComboBox
          Left = 327
          Top = 16
          Width = 182
          Height = 22
          Style = csOwnerDrawVariable
          ItemIndex = 0
          TabOrder = 3
          Text = #1048#1089#1087#1086#1083#1100#1079#1091#1077#1084#1099#1077' '#1085#1072' '#1089#1082#1083#1072#1076#1077
          OnClick = ei_optClick
          Items.Strings = (
            #1048#1089#1087#1086#1083#1100#1079#1091#1077#1084#1099#1077' '#1085#1072' '#1089#1082#1083#1072#1076#1077
            #1042#1089#1090#1088#1077#1095#1072#1102#1097#1080#1077#1089#1103' '#1074' '#1090#1077#1093#1085#1086#1083#1086#1075#1080#1103#1093
            #1055#1086#1083#1085#1099#1081' '#1089#1087#1080#1089#1086#1082)
        end
      end
      object TabSheet10: TTabSheet
        Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
        ImageIndex = -1
        ParentShowHint = False
        ShowHint = True
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object kz: TLabeledEdit
          Left = 1
          Top = 16
          Width = 48
          Height = 21
          EditLabel.Width = 43
          EditLabel.Height = 13
          EditLabel.Caption = #1050#1086#1076' '#1079#1072#1075'.'
          MaxLength = 3
          NumbersOnly = True
          TabOrder = 0
          OnChange = kzChange
          OnDblClick = kzDblClick
          OnExit = kzExit
        end
        object razmzagot: TLabeledEdit
          Left = 3
          Top = 54
          Width = 269
          Height = 21
          EditLabel.Width = 100
          EditLabel.Height = 13
          EditLabel.Caption = #1055#1088#1086#1092#1080#1083#1100' '#1080' '#1088#1072#1079#1084#1077#1088#1099
          TabOrder = 1
          OnChange = razmzagotChange
        end
        object kdz: TLabeledEdit
          Left = 130
          Top = 16
          Width = 55
          Height = 21
          EditLabel.Width = 49
          EditLabel.Height = 13
          EditLabel.Caption = #1050#1086#1083'. '#1076#1077#1090'.'
          NumbersOnly = True
          TabOrder = 2
          OnChange = kdzChange
        end
        object masz: TLabeledEdit
          Left = 55
          Top = 16
          Width = 69
          Height = 21
          EditLabel.Width = 53
          EditLabel.Height = 13
          EditLabel.Caption = #1052#1072#1089#1089#1072' '#1079#1072#1075'.'
          TabOrder = 3
          OnChange = DoubleFildChange
          OnEnter = maszEnter
          OnExit = maszExit
        end
        object norma: TLabeledEdit
          Left = 191
          Top = 16
          Width = 66
          Height = 21
          EditLabel.Width = 61
          EditLabel.Height = 13
          EditLabel.Caption = #1053#1086#1088#1084#1072' '#1088#1072#1089#1093'.'
          TabOrder = 4
          OnChange = DoubleFildChange
          OnEnter = normaEnter
          OnExit = normaExit
        end
        object LabeledEdit9: TLabeledEdit
          Left = 348
          Top = 16
          Width = 48
          Height = 21
          EditLabel.Width = 44
          EditLabel.Height = 13
          EditLabel.Caption = #1045#1076'. '#1085#1086#1088#1084
          Enabled = False
          NumbersOnly = True
          TabOrder = 5
        end
        object kim: TLabeledEdit
          Left = 263
          Top = 16
          Width = 79
          Height = 21
          EditLabel.Width = 79
          EditLabel.Height = 13
          EditLabel.Caption = #1050#1086#1101#1092'. '#1080#1089#1087'. '#1084#1072#1090'.'
          ReadOnly = True
          TabOrder = 6
        end
      end
      object transport: TTabSheet
        Caption = #1058#1088#1072#1085#1089#1087#1086#1088#1090'/'#1082#1086#1085#1090#1088#1086#1083#1100
        ImageIndex = -1
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object strpLabel: TLabel
          Left = 3
          Top = 49
          Width = 55
          Height = 13
          Caption = #1057#1090#1088#1086#1087#1086#1074#1082#1072
        end
        object Label5: TLabel
          Left = 3
          Top = 3
          Width = 24
          Height = 13
          Caption = #1058#1072#1088#1072
        end
        object Label2: TLabel
          Left = 231
          Top = 3
          Width = 49
          Height = 13
          Caption = #1050#1086#1085#1090#1088#1086#1083#1100
        end
        object strop: TEdit
          Left = 3
          Top = 65
          Width = 222
          Height = 21
          ParentShowHint = False
          ReadOnly = True
          ShowHint = False
          TabOrder = 0
          OnDblClick = stropDblClick
        end
        object tara: TEdit
          Left = 3
          Top = 22
          Width = 222
          Height = 21
          ParentShowHint = False
          ReadOnly = True
          ShowHint = False
          TabOrder = 1
          OnDblClick = taraDblClick
        end
        object control: TComboBox
          Left = 231
          Top = 22
          Width = 250
          Height = 19
          Style = csOwnerDrawVariable
          ItemHeight = 13
          TabOrder = 2
        end
      end
    end
  end
  object fcb: TComboBox
    Left = 224
    Top = 240
    Width = 145
    Height = 21
    TabOrder = 3
    Visible = False
    OnChange = fcbChange
    OnExit = fcbExit
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 121
    Width = 31
    Height = 296
    Align = alLeft
    ButtonHeight = 25
    ButtonWidth = 30
    Customizable = True
    EdgeInner = esNone
    EdgeOuter = esNone
    GradientEndColor = 13759468
    GradientStartColor = 14221053
    Images = ImageList1
    List = True
    GradientDirection = gdHorizontal
    ParentShowHint = False
    ShowHint = True
    TabOrder = 4
    object Savebtn: TToolButton
      Left = 0
      Top = 0
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      ImageIndex = 0
      Wrap = True
      OnClick = SavebtnClick
    end
    object printbtn: TToolButton
      Left = 0
      Top = 25
      Caption = 'printbtn'
      ImageIndex = 1
      OnClick = printbtnClick
    end
  end
  object ImageList1: TImageList
    Left = 736
    Top = 32
    Bitmap = {
      494C010102000500080010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B8B8
      AA009F9F8D009F9F8D009F9F8D009F9F8D009F9F8D009F9F8D009F9F8D009F9F
      8D00B8B8AA000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000AAAA
      990000000000000000000000000000000000FEFEFD00FEFEFD00FDFDFB00FEFE
      FB00AAAA99000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000080
      8000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C00000000000008080000000000000000000A4A4A40083838300838383007878
      780000000000FF964B00FFC79E00D6C8A6006380410087673000A8754200FCFC
      F800787878008383830083838300A4A4A4000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000080
      8000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C0000000000000808000000000000000000098989800C5BDBD00C5BABA005959
      5900595959005959590059595900595959005959590059595900595959005959
      590059595900CCBBBB00CCBBBB00989898000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000080
      8000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C00000000000008080000000000000000000A1A1A100C4C2C200B8B0B0006F6B
      6B00968A8A009588880096878700968787009687870097878700978787009787
      870071696900CCBBBB00CCBBBB00A1A1A1000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000080
      8000000000000000000000000000000000000000000000000000000000000000
      000000000000008080000000000000000000AAAAAA00B8B8B800A5A5A5002020
      2000605454005A4D4D005A4D4D005A4D4D005A4D4D005A4D4D005A4D4D005A4D
      4D00202020009D9D9D00AFAFAF00AAAAAA000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000080
      8000008080000080800000808000008080000080800000808000008080000080
      800000808000008080000000000000000000BDBDBD00CFCFCF00BEBEBE003131
      31005C5656004D4444004D4444004D4444004D4444004D4444004D4444004E46
      46003131310066FF6600BEB3B300BDBDBD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000080
      8000000000000000000000000000000000000000000000000000000000000000
      000000808000008080000000000000000000D0D0D000C1C1C100C9C9C9004444
      44006766660049464600403C3C003F3B3B003F3B3B003F3B3B003F3B3B004844
      440044444400BBB1B100B0ABAB00D0D0D0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000000
      0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C00000000000008080000000000000000000E2E2E200BABABA00DADADA005858
      580076767600666666005F5F5F0052515100444343003C3B3B00373636004A49
      490058585800BFB9B900B2B1B100E2E2E2000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000000
      0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C00000000000008080000000000000000000F1F1F100BCBCBC00E8E8E8006868
      6800838383007D7D7D007D7D7D007D7D7D007D7D7D007D7D7D007C7C7C008080
      800068686800E4E4E400BBBBBB00F1F1F1000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000000
      0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C00000000000008080000000000000000000FDFDFD00CBCBCB00B9B9B9007474
      7400757575007575750075757500757575007575750075757500757575007575
      750074747400B9B9B900CBCBCB00FDFDFD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000000
      0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C00000000000008080000000000000000000000000000000000000000000D5D5
      C500FAFAF400F5F5ED00F2F2EA00EEEEE200E8E8D900E6E6D500E5E5D400F2F2
      E100D5D5C5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000000
      0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C00000000000000000000000000000000000000000000000000000000000D7D7
      C600FAFAF300F2F2EA00EEEEE200E8E8D900E6E6D500B5B5A400B5B5A400B5B5
      A400B7B7A5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008080000000
      0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C00000000000C0C0C0000000000000000000000000000000000000000000D9D9
      C800F9F9F000EEEEE200E8E8D900E6E6D500E5E5D400C7C7B60000000000D9D9
      C800F1F1EC000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DBDB
      CA00FBFBEF00F4F4E500F3F3E200F2F2E100F2F2E100D3D3C200DBDBCA00F2F2
      EC00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E5E5
      D800DDDDCC00DDDDCC00DDDDCC00DDDDCC00DDDDCC00DDDDCC00F3F3ED000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFE00700000000C001EF0700000000
      8001080000000000800100000000000080010000000000008001000000000000
      8001000000000000800100000000000080010000000000008001000000000000
      80010000000000008001E007000000008001E007000000008001E02700000000
      8001E00F00000000FFFFE01F0000000000000000000000000000000000000000
      000000000000}
  end
  object PAB: TPopupActionBar
    OnPopup = PABPopup
    Left = 520
    Top = 184
    object N12: TMenuItem
      Caption = #1042#1089#1090#1072#1074#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
      OnClick = N12Click
    end
    object N4: TMenuItem
      Caption = #1042#1099#1088#1077#1079#1072#1090#1100
      OnClick = N4Click
    end
    object N1: TMenuItem
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1042#1089#1090#1072#1074#1080#1090#1100
      OnClick = N2Click
    end
    object N3: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = N3Click
    end
    object N5: TMenuItem
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      OnClick = N5Click
    end
  end
  object PAB2: TPopupActionBar
    OnPopup = PABPopup
    Left = 320
    Top = 472
    object C1: TMenuItem
      Caption = 'C'#1080#1084#1074#1086#1083
      OnClick = C1Click
    end
    object N7: TMenuItem
      Action = EditCut1
      Caption = #1042#1099#1088#1077#1079#1072#1090#1100
    end
    object N6: TMenuItem
      Action = EditCopy1
    end
    object N8: TMenuItem
      Action = EditPaste1
    end
    object N9: TMenuItem
      Action = EditSelectAll1
    end
    object N10: TMenuItem
      Action = EditDelete1
    end
    object N11: TMenuItem
      Action = EditUndo1
    end
  end
  object ActionList1: TActionList
    Left = 56
    Top = 288
    object EditCut1: TEditCut
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      ImageIndex = 0
      ShortCut = 16472
    end
    object EditCopy1: TEditCopy
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      Hint = 'Copy|Copies the selection and puts it on the Clipboard'
      ImageIndex = 1
      ShortCut = 16451
    end
    object EditPaste1: TEditPaste
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1042#1089#1090#1072#1074#1080#1090#1100
      Hint = 'Paste|Inserts Clipboard contents'
      ImageIndex = 2
      ShortCut = 16470
    end
    object EditSelectAll1: TEditSelectAll
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1042#1099#1076#1077#1083#1080#1090#1100' '#1074#1089#1077
      Hint = 'Select All|Selects the entire document'
      ShortCut = 16449
    end
    object EditUndo1: TEditUndo
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1064#1072#1075' '#1085#1072#1079#1072#1076
      Hint = 'Undo|Reverts the last action'
      ImageIndex = 3
      ShortCut = 16474
    end
    object EditDelete1: TEditDelete
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Hint = 'Delete|Erases the selection'
      ImageIndex = 5
      ShortCut = 8238
    end
  end
  object Timer: TTimer
    Interval = 60000
    OnTimer = TimerTimer
    Left = 696
    Top = 176
  end
end
