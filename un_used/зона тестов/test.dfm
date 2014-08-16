object Form1: TForm1
  Left = 0
  Top = 0
  ClientHeight = 599
  ClientWidth = 770
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 770
    Height = 599
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 877
    ExplicitHeight = 639
    object TabSheet2: TTabSheet
      Caption = 'TabSheet2'
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 28
      ExplicitWidth = 869
      ExplicitHeight = 611
      DesignSize = (
        762
        571)
      object Obd: TEdit
        Left = 3
        Top = 3
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '971171000000000'
      end
      object RepStart: TButton
        Left = 194
        Top = 1
        Width = 87
        Height = 25
        Caption = #1047#1072#1087#1091#1082' '#1086#1090#1095#1077#1090#1072
        TabOrder = 1
        OnClick = RepStartClick
      end
      object ClearLog: TButton
        Left = 287
        Top = 1
        Width = 87
        Height = 25
        Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1083#1086#1075
        TabOrder = 2
        OnClick = ClearLogClick
      end
      object GetLog: TButton
        Left = 380
        Top = 1
        Width = 87
        Height = 25
        Caption = #1051#1086#1075
        TabOrder = 3
        OnClick = GetLogClick
      end
      object Log: TMemo
        Left = 3
        Top = 32
        Width = 756
        Height = 537
        Anchors = [akLeft, akTop, akRight, akBottom]
        TabOrder = 4
        ExplicitWidth = 863
        ExplicitHeight = 577
      end
      object RepNo: TEdit
        Left = 130
        Top = 3
        Width = 58
        Height = 21
        NumbersOnly = True
        TabOrder = 5
        Text = '8'
      end
    end
  end
  object ADC: TADOConnection
    ConnectionString = 'FILE NAME=E:\YZPM_KTPP\Debug\Win32\lib\connect.udl'
    LoginPrompt = False
    Provider = 'E:\YZPM_KTPP\Debug\Win32\lib\connect.udl'
    Left = 72
    Top = 104
  end
  object OD: TOpenDialog
    Left = 424
    Top = 112
  end
end
