object OASUtrasfer: TOASUtrasfer
  Left = 0
  Top = 0
  Caption = #1054#1090#1087#1088#1072#1074#1082#1072' '#1076#1072#1085#1085#1099#1093' '#1085#1072' '#1040#1057#1059
  ClientHeight = 505
  ClientWidth = 729
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 729
    Height = 505
    Align = alClient
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 727
      Height = 503
      ActivePage = TS3
      Align = alClient
      TabOrder = 0
      object TS3: TTabSheet
        Caption = #1048#1079#1084#1077#1085#1077#1085#1080#1103
        ImageIndex = 2
        OnShow = TS3Show
        object Panel3: TPanel
          Left = 0
          Top = 0
          Width = 121
          Height = 475
          Align = alLeft
          TabOrder = 0
          object _table: TRadioGroup
            Left = 1
            Top = 1
            Width = 119
            Height = 96
            Align = alTop
            Caption = #1058#1072#1073#1083#1080#1094#1072
            Columns = 2
            ItemIndex = 0
            Items.Strings = (
              'nsi001'
              'nsi002'
              'nsi003'
              'nsi004'
              'nsi005'
              'nsi006'
              'nsi009'
              'nsi010')
            TabOrder = 0
            OnClick = _tableClick
          end
          object Button1: TButton
            Left = 1
            Top = 103
            Width = 114
            Height = 25
            Caption = #1054#1090#1084#1077#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
            TabOrder = 1
            OnClick = Button1Click
          end
        end
        object table: TStringGrid
          Left = 121
          Top = 0
          Width = 598
          Height = 475
          Align = alClient
          DefaultColWidth = 16
          DefaultRowHeight = 16
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          TabOrder = 1
        end
      end
    end
  end
  object ADC: TADOConnection
    ConnectionString = 'FILE NAME=\\Skb35\'#1087#1088#1086#1075#1088#1072#1084#1084#1099'\lib\connect.udl'
    Provider = '\\Skb35\'#1087#1088#1086#1075#1088#1072#1084#1084#1099'\lib\connect.udl'
    Left = 384
    Top = 64
  end
end
