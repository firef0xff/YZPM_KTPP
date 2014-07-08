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
        MultiSelect = True
        MultiSelectStyle = [msControlSelect, msShiftSelect, msSiblingOnly]
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
          OnKeyPress = StartedParamsKeyPress
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
          OnClick = FindStartedClick
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
        MultiSelect = True
        MultiSelectStyle = [msControlSelect, msShiftSelect, msSiblingOnly]
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
          OnKeyPress = NewParamsKeyPress
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
      Caption = #1056#1072#1089#1095#1077#1090
      ImageIndex = 1
      object Panel5: TPanel
        Left = 0
        Top = 0
        Width = 496
        Height = 89
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        ExplicitLeft = -1
        ExplicitTop = -6
        DesignSize = (
          496
          89)
        object Label3: TLabel
          Left = 407
          Top = 70
          Width = 85
          Height = 13
          Anchors = [akRight, akBottom]
          Caption = #1089#1090#1088#1072#1085#1080#1094' '#1085#1072' '#1092#1072#1081#1083
        end
        object ToExcel: TBitBtn
          Left = 416
          Top = 2
          Width = 75
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = #1042' Excel'
          DoubleBuffered = True
          Glyph.Data = {
            36090000424D3609000000000000360000002800000018000000180000000100
            2000000000000009000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00417B
            5700214F3900214F3900214F3900214F39001A4533001A4533001A4533001A45
            33001A45330013352900133529001335290013352900133529000D281F000D28
            1F000D281F000D281F000A1F19000A1F19000A1F1900FFFFFF00FFFFFF00417B
            57006C977E005176660051766600517666005176660051766600517666004B6B
            60004B6B60004B6B60004B6B60004B6B6000435F5900435F5900435F5900435F
            5900435F5900435F5900435F5900435F59000A1F1900FFFFFF00FFFFFF004781
            5D006C977E00E8F1E800E8F1E800E6F0E600E2EEE300E2EEE300E0EEE000DFEC
            DF00DCEADB00DCEADB00DAE9DA00D9E8D900D8E7D800D5E5D500D5E5D500D5E5
            D500D2E4D200D2E4D200D2E4D200435F59000A1F1900FFFFFF00FFFFFF004781
            5D006C977E00EAF2E900E8F1E800E8F1E800E4EFE400E2EEE300E2EEE300E0EE
            E000DEEBDE00DCEADB00DCEADB00DAE9DA00D8E7D800D8E7D800D5E5D500D5E5
            D500D2E4D200D2E4D200D2E4D200435F59000D281F00FFFFFF00FFFFFF004781
            5D006C977E00EBF3EB00EAF2E900E8F1E800E6F0E600E4EFE400E2EEE300E2EE
            E300DFECDF00DEEBDE00DCEADB00DCEADB00D9E8D900D8E7D800D8E7D800D5E5
            D500D5E5D500D2E4D200D2E4D200435F59000D281F00FFFFFF00FFFFFF004D87
            62006C977E00EDF5ED00EDF5ED00EBF3EB00E8F1E800E8F1E800E6F0E600E4EF
            E400E2EEE300E0EEE000DFECDF00AAD6B20026422D00213B2700213B2700213B
            2700213B2700213B2700D5E5D500435F59000D281F00FFFFFF00FFFFFF004D87
            620076A08600EFF6EF004B964D0026422D0026422D0026422D0026422D002642
            2D0026422D0026422D001A4D2A000F60150032873500127437001C6C3A002C66
            42003A5F5100213B2700D5E5D500435F59000D281F00FFFFFF00FFFFFF00558E
            670076A08600F1F7F1004B964D00127437001C6C3A001C6C3A002C6642002C66
            42003A5F51003A5F5100046904001D781E006DB675002D8747002D874700227F
            400004690400D8E7D800D5E5D500435F590013352900FFFFFF00FFFFFF00558E
            670076A08600F3F8F300DAE9DA004B964D0073BB7C0073BB7C006DB6750068B0
            6F0055A45A0004690400409347009DD0A70040934700358C4F002D8747002D87
            470094C79C00D8E7D800D8E7D800435F590013352900FFFFFF00FFFFFF005896
            6B0076A08600F5F9F500F3F8F300F3F8F3004B964D006DB6750068B06F0055A4
            5A00409347009DD0A7006DB6750055A45A00499B5400499B5400046904002D87
            47000F601500DAE9DA00D9E8D9004B6B600013352900FFFFFF00FFFFFF005896
            6B0081AA8D00F6FAF500F5F9F500F3F8F300DAE9DA004B964D0055A45A000469
            0400AAD6B20073BB7C0055A45A0055A45A0055A45A00046904003A734C005782
            5A0057825A00DCEADB00DAE9DA004B6B600013352900FFFFFF00FFFFFF005F9B
            720081AA8D00F6FAF600F6FAF500F5F9F500F3F8F300DAE9DA001D781E004093
            47007CC185005CAA65005CAA650055A45A003A734C00A8C2A800E2EEE300E0EE
            E000DEEBDE00DCEADB00DCEADB004B6B600013352900FFFFFF00FFFFFF005F9B
            720081AA8D00F8FAF800F6FAF600F6FAF500F3F8F30094C79C004B964D00BADE
            C00064AC690064AC69005CAA650055A45A0004690400CDDACD00E2EEE300E2EE
            E300DFECDF00DEEBDE00DCEADB004B6B60001A453300FFFFFF00FFFFFF0066A0
            770081AA8D00FAFDFA00F9FBFA00F8FAF80055A45A00C4E5CA0094C79C0073BB
            7C006DB6750064AC690057825A0068B06F0055A45A0057825A0004690400CDDA
            CD00E2EEE300E0EEE000DFECDF00517666001A453300FFFFFF00FFFFFF0066A0
            770081AA8D00FAFDFA00FAFDFA0094C79C00C4E5CA0088C792007CC185007CC1
            850068B06F0057825A0068B06F0073BB7C006DB6750055A45A0057825A000469
            0400E2EEE300E2EEE300E0EEE000517666001A453300FFFFFF00FFFFFF006CA6
            7C008AB79500FBFEFB0094C79C0068B06F009DD0A70088C792007CC185007CC1
            850061996400A8C2A800619964006DB6750073BB7C006DB6750055A45A005782
            5A00CDDACD00E2EEE300E2EEE300517666001A453300FFFFFF00FFFFFF006CA6
            7C008AB79500FDFEFD006DB67500C4E5CA0088C7920088C7920088C7920073BA
            8300D8E7D800F3F8F300CDDACD006199640073BB7C0073BB7C006DB6750055A4
            5A0004690400E4EFE400E2EEE300517666001A453300FFFFFF00FFFFFF0071AA
            81008AB79500FFFFFF00FEFFFE00FDFEFD00FAFDFA00FAFDFA00F9FBFA00F8FA
            F800F6FAF500F5F9F500F3F8F300F3F8F300EFF6EF00EDF5ED00EDF5ED00EBF3
            EB00E8F1E800E8F1E800E6F0E60051766600214F3900FFFFFF00FFFFFF0071AA
            81008AB79500FFFFFF00FFFFFF00FEFFFE00FBFEFB00FAFDFA00FAFDFA00F9FB
            FA00F6FAF600F6FAF500F5F9F500F3F8F300F1F7F100EFF6EF00EDF5ED00EDF5
            ED00EAF2E900E8F1E800E8F1E80051766600214F3900FFFFFF00FFFFFF0071AA
            81008AB79500FFFFFF00FFFFFF00FFFFFF00FDFEFD00FBFEFB00FAFDFA00FAFD
            FA00F8FAF800F6FAF600F6FAF500F5F9F500F3F8F300F1F7F100EFF6EF00EDF5
            ED00EBF3EB00EAF2E900E8F1E80051766600214F3900FFFFFF00FFFFFF0076AF
            850081AA8D008AB795008AB795008AB795008AB795008AB795008AB7950081AA
            8D0081AA8D0081AA8D0081AA8D0076A0860076A0860076A0860076A0860076A0
            86006C977E006C977E006C977E006C977E00214F3900FFFFFF00FFFFFF0076AF
            850076AF850071AA810071AA810071AA81006CA67C006CA67C0066A0770066A0
            77005F9B72005F9B72005F9B720058966B00558E6700558E67004D8762004D87
            620047815D0047815D0047815D00417B5700417B5700FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
          ParentDoubleBuffered = False
          TabOrder = 0
          OnClick = ToExcelClick
        end
        object StartCalck: TBitBtn
          Left = 335
          Top = 2
          Width = 75
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = #1056#1072#1089#1095#1080#1090#1072#1090#1100
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 1
          OnClick = StartCalckClick
        end
        object CalckPeroid: TRadioGroup
          Left = 2
          Top = 2
          Width = 119
          Height = 81
          Caption = #1055#1077#1088#1080#1086#1076' '#1088#1072#1089#1095#1077#1090#1072
          ItemIndex = 0
          Items.Strings = (
            #1052#1077#1089#1103#1094
            #1050#1074#1072#1088#1090#1072#1083
            #1043#1086#1076
            #1055#1088#1086#1080#1079#1074#1086#1083#1100#1085#1099#1081)
          TabOrder = 2
        end
        object MonthDays: TLabeledEdit
          Left = 127
          Top = 16
          Width = 114
          Height = 21
          EditLabel.Width = 117
          EditLabel.Height = 13
          EditLabel.Caption = #1056#1072#1073#1086#1095#1080#1093' '#1076#1085#1077#1081' '#1074' '#1084#1077#1089#1103#1094#1077
          NumbersOnly = True
          TabOrder = 3
          Text = '22'
        end
        object PeriodDays: TLabeledEdit
          Left = 127
          Top = 58
          Width = 114
          Height = 21
          EditLabel.Width = 81
          EditLabel.Height = 13
          EditLabel.Caption = #1044#1085#1077#1081' '#1074' '#1087#1077#1088#1080#1086#1076#1077
          NumbersOnly = True
          TabOrder = 4
          Text = '22'
        end
        object SetFile: TButton
          Left = 447
          Top = 33
          Width = 40
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = '...'
          TabOrder = 5
          OnClick = SetFileClick
        end
        object FileName: TLabeledEdit
          Left = 247
          Top = 35
          Width = 194
          Height = 21
          Anchors = [akRight, akBottom]
          EditLabel.Width = 80
          EditLabel.Height = 13
          EditLabel.Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082':'
          TabOrder = 6
          OnChange = FileNameChange
        end
        object ActiveDelimiter: TCheckBox
          Left = 273
          Top = 66
          Width = 89
          Height = 17
          Anchors = [akRight, akBottom]
          Caption = #1056#1072#1079#1073#1080#1074#1072#1090#1100' '#1087#1086' '
          TabOrder = 7
        end
        object Count: TEdit
          Left = 368
          Top = 62
          Width = 33
          Height = 21
          Anchors = [akRight, akBottom]
          NumbersOnly = True
          TabOrder = 8
          Text = '100'
        end
      end
      object Previe: TStringGrid
        Left = 0
        Top = 89
        Width = 496
        Height = 454
        Align = alClient
        ColCount = 9
        DefaultColWidth = 16
        DefaultRowHeight = 16
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
        PopupMenu = PAB3
        TabOrder = 1
        ExplicitLeft = -1
      end
    end
  end
  object PAB1: TPopupActionBar
    Left = 72
    Top = 152
    object AddStarted: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      OnClick = AddStartedClick
    end
  end
  object PAB2: TPopupActionBar
    Left = 104
    Top = 240
    object AddNew: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      OnClick = AddNewClick
    end
  end
  object PAB3: TPopupActionBar
    Left = 520
    Top = 160
    object StartedClear: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1077
      OnClick = StartedClearClick
    end
    object StartedRemove: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1099#1077
      OnClick = StartedRemoveClick
    end
  end
  object PAB4: TPopupActionBar
    Left = 512
    Top = 416
    object NewClear: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1077
      OnClick = NewClearClick
    end
    object NewRemove: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1099#1077
      OnClick = NewRemoveClick
    end
  end
  object SD: TSaveDialog
    Filter = 'Excel|*.xls; *.xlsx;'
    Left = 480
    Top = 80
  end
end
