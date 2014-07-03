object ResourceUsage: TResourceUsage
  Left = 0
  Top = 0
  Width = 734
  Height = 571
  TabOrder = 0
  object Splitter1: TSplitter
    Left = 227
    Top = 0
    Height = 571
    ExplicitLeft = 208
    ExplicitTop = 64
    ExplicitHeight = 100
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 227
    Height = 571
    ActivePage = TabSheet2
    Align = alLeft
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1047#1072#1087#1091#1097#1077#1085#1085#1099#1077' '#1079#1072#1082#1072#1079#1099
      object ManufactureTree: TTreeView
        Left = 0
        Top = 73
        Width = 219
        Height = 470
        Align = alClient
        BorderStyle = bsNone
        Indent = 19
        PopupMenu = PAB1
        TabOrder = 0
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 219
        Height = 73
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          219
          73)
        object StartedParams: TLabeledEdit
          Left = 4
          Top = 16
          Width = 213
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          EditLabel.Width = 32
          EditLabel.Height = 13
          EditLabel.Caption = #1048#1097#1077#1084':'
          TabOrder = 0
        end
        object FindStarted: TButton
          Left = 142
          Top = 43
          Width = 75
          Height = 21
          Anchors = [akTop, akRight]
          Caption = #1054#1090#1086#1073#1088#1072#1090#1100
          TabOrder = 1
          OnClick = FindStartedClick
        end
        object Show_Closed: TCheckBox
          Left = 4
          Top = 43
          Width = 111
          Height = 17
          Caption = #1047#1072#1082#1088#1099#1090#1099#1077' '#1079#1072#1082#1072#1079#1099
          TabOrder = 2
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1053#1086#1074#1099#1077' '#1079#1072#1082#1072#1079#1099
      ImageIndex = 1
      object DevelopTree: TTreeView
        Left = 0
        Top = 73
        Width = 219
        Height = 470
        Align = alClient
        BevelEdges = []
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        Indent = 19
        PopupMenu = PAB2
        TabOrder = 0
      end
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 219
        Height = 73
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          219
          73)
        object NewParams: TLabeledEdit
          Left = 4
          Top = 16
          Width = 213
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          EditLabel.Width = 32
          EditLabel.Height = 13
          EditLabel.Caption = #1048#1097#1077#1084':'
          TabOrder = 0
        end
        object FindNew: TButton
          Left = 142
          Top = 43
          Width = 75
          Height = 21
          Anchors = [akTop, akRight]
          Caption = #1054#1090#1086#1073#1088#1072#1090#1100
          TabOrder = 1
          OnClick = FindNewClick
        end
      end
    end
  end
  object PageControl2: TPageControl
    Left = 230
    Top = 0
    Width = 504
    Height = 571
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 1
    object TabSheet3: TTabSheet
      Caption = #1053#1072#1073#1086#1088' '#1076#1083#1103' '#1088#1072#1089#1095#1077#1090#1072
      object Splitter2: TSplitter
        Left = 0
        Top = 277
        Width = 496
        Height = 3
        Cursor = crVSplit
        Align = alBottom
        ExplicitTop = 272
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 496
        Height = 277
        Align = alClient
        TabOrder = 0
        object Label1: TLabel
          Left = 1
          Top = 1
          Width = 494
          Height = 13
          Align = alTop
          Alignment = taCenter
          Caption = #1055#1083#1072#1085' '#1087#1086' '#1079#1072#1087#1091#1097#1077#1085#1085#1099#1084' '#1079#1072#1082#1072#1079#1072#1084
          ExplicitWidth = 150
        end
        object zap_sg: TStringGrid
          Left = 1
          Top = 14
          Width = 494
          Height = 262
          Align = alClient
          ColCount = 8
          DefaultColWidth = 16
          DefaultRowHeight = 16
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
          PopupMenu = PAB3
          TabOrder = 0
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 280
        Width = 496
        Height = 263
        Align = alBottom
        TabOrder = 1
        object Label2: TLabel
          Left = 1
          Top = 1
          Width = 494
          Height = 13
          Align = alTop
          Alignment = taCenter
          Caption = #1055#1083#1072#1085' '#1087#1086' '#1085#1086#1074#1099#1084' '#1079#1072#1082#1072#1079#1072#1084
          ExplicitWidth = 118
        end
        object plan_sg: TStringGrid
          Left = 1
          Top = 14
          Width = 494
          Height = 248
          Align = alClient
          ColCount = 8
          DefaultColWidth = 16
          DefaultRowHeight = 16
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
          PopupMenu = PAB4
          TabOrder = 0
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1088#1072#1089#1095#1077#1090#1072
      ImageIndex = 1
    end
  end
  object PAB1: TPopupActionBar
    Left = 72
    Top = 152
    object N1: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074#1089#1077
    end
    object N2: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1079#1072#1087#1091#1097#1077#1085#1085#1099#1077
    end
    object N3: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1085#1077' '#1079#1072#1087#1091#1097#1077#1085#1085#1099#1077
    end
  end
  object PAB2: TPopupActionBar
    Left = 104
    Top = 240
    object MenuItem3: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    end
  end
  object PAB3: TPopupActionBar
    Left = 520
    Top = 160
    object MenuItem4: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1077
    end
    object MenuItem5: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1099#1077
    end
  end
  object PAB4: TPopupActionBar
    Left = 512
    Top = 416
    object MenuItem6: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1077
    end
    object MenuItem7: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1099#1077
    end
  end
end
