object Form1: TForm1
  Left = 0
  Top = 0
  ClientHeight = 639
  ClientWidth = 877
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
    Width = 877
    Height = 639
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'TabSheet1'
      DesignSize = (
        869
        611)
      object Edit1: TEdit
        Left = 3
        Top = 572
        Width = 753
        Height = 21
        Anchors = [akLeft, akRight, akBottom]
        TabOrder = 0
        Text = 'Edit1'
      end
      object Button1: TButton
        Left = 791
        Top = 91
        Width = 75
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Button1'
        TabOrder = 1
      end
      object Memo1: TMemo
        Left = 3
        Top = 3
        Width = 782
        Height = 563
        Anchors = [akLeft, akTop, akRight, akBottom]
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssBoth
        TabOrder = 2
      end
      object Button2: TButton
        Left = 791
        Top = 122
        Width = 75
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Button1'
        TabOrder = 3
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 791
        Top = 153
        Width = 75
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Button1'
        TabOrder = 4
      end
      object Button4: TButton
        Left = 791
        Top = 184
        Width = 75
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Button1'
        TabOrder = 5
      end
      object Button5: TButton
        Left = 791
        Top = 215
        Width = 75
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Button1'
        TabOrder = 6
      end
      object Button6: TButton
        Left = 791
        Top = 246
        Width = 75
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Button1'
        TabOrder = 7
      end
      object Button7: TButton
        Left = 791
        Top = 277
        Width = 75
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Button1'
        TabOrder = 8
      end
      object Button8: TButton
        Left = 791
        Top = 308
        Width = 75
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Button1'
        TabOrder = 9
      end
    end
    object ts: TTabSheet
      Caption = 'ts'
      ImageIndex = 1
      object ComboBox1: TComboBox
        Left = 16
        Top = 200
        Width = 145
        Height = 21
        Style = csDropDownList
        Enabled = False
        ItemIndex = 5
        TabOrder = 0
        Text = '4'
        Items.Strings = (
          '1'
          '2'
          '2'
          '34'
          '23'
          '4'
          '54'
          '5'
          '5')
      end
    end
    object ts2: TTabSheet
      Caption = 'ts2'
      ImageIndex = 2
    end
    object ts1: TTabSheet
      Caption = 'ts1'
      ImageIndex = 3
    end
    object ts3: TTabSheet
      Caption = 'ts3'
      ImageIndex = 5
    end
    object TabSheet4: TTabSheet
      Caption = 'TabSheet4'
      ImageIndex = 6
    end
    object TabSheet2: TTabSheet
      Caption = 'TabSheet2'
      ImageIndex = 6
      object Edit2: TEdit
        Left = 208
        Top = 152
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '971171000000000'
      end
      object Button9: TButton
        Left = 384
        Top = 216
        Width = 75
        Height = 25
        Caption = 'Button9'
        TabOrder = 1
        OnClick = Button9Click
      end
    end
  end
  object ADC: TADOConnection
    ConnectionString = 'FILE NAME=E:\YZPM_KTPP\Debug\Win32\lib\connect.udl'
    LoginPrompt = False
    Provider = 'E:\YZPM_KTPP\Debug\Win32\lib\connect.udl'
    Left = 160
    Top = 56
  end
  object OD: TOpenDialog
    Left = 424
    Top = 112
  end
end
