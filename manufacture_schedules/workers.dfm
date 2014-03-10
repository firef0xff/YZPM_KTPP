object WorkersSettings: TWorkersSettings
  Left = 0
  Top = 0
  Width = 654
  Height = 472
  TabOrder = 0
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 177
    Height = 472
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 0
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 177
      Height = 22
      Align = alTop
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = #1043#1088#1091#1087#1087#1099' '#1088#1072#1073#1086#1095#1080#1093
      TabOrder = 0
    end
    object sgGroups: TStringGrid
      Left = 0
      Top = 22
      Width = 177
      Height = 450
      Align = alClient
      BevelInner = bvNone
      BevelKind = bkTile
      BevelOuter = bvNone
      ColCount = 3
      DefaultColWidth = 16
      DefaultRowHeight = 16
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      PopupMenu = PAB1
      TabOrder = 1
      OnSelectCell = sgGroupsSelectCell
    end
  end
  object Panel3: TPanel
    Left = 177
    Top = 0
    Width = 477
    Height = 472
    Align = alClient
    BevelOuter = bvNone
    Caption = 'Panel3'
    TabOrder = 1
    object sgWorkers: TStringGrid
      Left = 0
      Top = 22
      Width = 477
      Height = 450
      Align = alClient
      BevelInner = bvNone
      BevelKind = bkTile
      BevelOuter = bvNone
      ColCount = 6
      DefaultColWidth = 16
      DefaultRowHeight = 16
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      PopupMenu = PAB2
      TabOrder = 0
    end
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 477
      Height = 22
      Align = alTop
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = #1056#1072#1073#1086#1095#1080#1077
      TabOrder = 1
    end
  end
  object PAB1: TPopupActionBar
    Left = 64
    Top = 128
    object N1: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      OnClick = N1Click
    end
    object N6: TMenuItem
      Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
      OnClick = N6Click
    end
    object N2: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = N2Click
    end
  end
  object PAB2: TPopupActionBar
    Left = 256
    Top = 160
    object N3: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      OnClick = N3Click
    end
    object N4: TMenuItem
      Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
      OnClick = N4Click
    end
    object N5: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = N5Click
    end
  end
end
