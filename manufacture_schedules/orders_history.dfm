object winEditOrdersHistory: TwinEditOrdersHistory
  Left = 0
  Top = 0
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' '#1085#1072#1088#1103#1076
  ClientHeight = 194
  ClientWidth = 455
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object SGOrdersHistory: TStringGrid
    Left = 0
    Top = 0
    Width = 455
    Height = 194
    Align = alClient
    ColCount = 6
    DefaultColWidth = 16
    DefaultRowHeight = 16
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    PopupMenu = CMOrdHistory
    TabOrder = 0
    OnMouseDown = SGOrdersHistoryMouseDown
    ExplicitLeft = 8
    ExplicitTop = -16
  end
  object CMOrdHistory: TPopupMenu
    Left = 240
    Top = 128
    object N1: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = N1Click
    end
  end
end
