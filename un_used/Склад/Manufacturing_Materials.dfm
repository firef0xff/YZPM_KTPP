object Materials_Need: TMaterials_Need
  Left = 0
  Top = 0
  Caption = #1047#1072#1087#1091#1089#1082#1080' '#1080' '#1084#1072#1090#1077#1088#1080#1072#1083#1099
  ClientHeight = 646
  ClientWidth = 844
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter2: TSplitter
    Left = 0
    Top = 445
    Width = 844
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    AutoSnap = False
    ExplicitTop = 359
    ExplicitWidth = 760
  end
  object Panel18: TPanel
    Left = 0
    Top = 0
    Width = 844
    Height = 445
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object Splitter3: TSplitter
      Left = 393
      Top = 0
      Height = 445
      AutoSnap = False
      ExplicitHeight = 503
    end
    object materials_lists: TPageControl
      Left = 396
      Top = 0
      Width = 448
      Height = 445
      ActivePage = TabSheet1
      Align = alClient
      Constraints.MinHeight = 445
      Constraints.MinWidth = 448
      TabOrder = 0
      OnChange = materials_listsChange
      object TabSheet1: TTabSheet
        Caption = #1059#1079#1083#1099'/'#1044#1077#1090#1072#1083#1080
        ImageIndex = 3
        object Dets: TStringGrid
          Left = 0
          Top = 0
          Width = 440
          Height = 417
          Align = alClient
          ColCount = 7
          DefaultColWidth = 16
          DefaultRowHeight = 16
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect]
          TabOrder = 0
          OnDrawCell = ContentGridsDrawCell
          ColWidths = (
            16
            16
            16
            16
            16
            16
            16)
        end
      end
      object TabSheet4: TTabSheet
        Tag = 1
        Caption = #1057#1090#1072#1085#1076#1072#1088#1090#1085#1099#1077' '#1080#1079#1076#1077#1083#1080#1103
        object Std_izd: TStringGrid
          Left = 0
          Top = 0
          Width = 440
          Height = 417
          Align = alClient
          ColCount = 7
          DefaultColWidth = 16
          DefaultRowHeight = 16
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect]
          TabOrder = 0
          OnDrawCell = ContentGridsDrawCell
        end
      end
      object TabSheet5: TTabSheet
        Tag = 2
        Caption = #1052#1072#1090#1077#1088#1080#1072#1083#1099
        ImageIndex = 1
        object Materials: TStringGrid
          Left = 0
          Top = 0
          Width = 440
          Height = 417
          Align = alClient
          ColCount = 7
          DefaultColWidth = 16
          DefaultRowHeight = 16
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect]
          TabOrder = 0
          OnDrawCell = ContentGridsDrawCell
        end
      end
      object TabSheet6: TTabSheet
        Tag = 3
        Caption = #1042#1089#1087#1086#1084#1086#1075#1072#1090#1077#1083#1100#1085#1099#1077' '#1084#1072#1090#1077#1088#1080#1072#1083#1099
        ImageIndex = 2
        object Vspom_mat: TStringGrid
          Left = 0
          Top = 0
          Width = 440
          Height = 417
          Align = alClient
          ColCount = 7
          DefaultColWidth = 16
          DefaultRowHeight = 16
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect]
          TabOrder = 0
          OnDrawCell = ContentGridsDrawCell
        end
      end
    end
    object Panel15: TPanel
      Left = 0
      Top = 0
      Width = 393
      Height = 445
      Align = alLeft
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = #1057#1087#1080#1089#1086#1082' '#1079#1072#1082#1072#1079#1086#1074' '#1074' '#1079#1072#1087#1091#1089#1082#1077
      Constraints.MinHeight = 150
      Constraints.MinWidth = 390
      TabOrder = 1
      object Tree: TTreeView
        Left = 0
        Top = 0
        Width = 389
        Height = 351
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        Indent = 19
        PopupMenu = PAB1
        TabOrder = 0
        OnDeletion = TreeDeletion
        OnExpanding = TreeExpanding
        OnMouseDown = TreeMouseDown
        Items.NodeData = {
          0301000000280000000000000000000000FFFFFFFFFFFFFFFF00000000000000
          00010000000105370430043A04300437042A0000000000000000000000FFFFFF
          FFFFFFFFFF00000000000000000100000001063F0430044004420438044F042C
          0000000000000000000000FFFFFFFFFFFFFFFF00000000000000000100000001
          0718043704340435043B04380435042A0000000000000000000000FFFFFFFFFF
          FFFFFF000000000000000000000000010621043E044104420430043204}
        ExplicitLeft = -1
        ExplicitTop = -1
      end
      object Panel17: TPanel
        Left = 0
        Top = 351
        Width = 389
        Height = 90
        Align = alBottom
        BevelEdges = [beTop]
        BevelKind = bkTile
        BevelOuter = bvNone
        Constraints.MinHeight = 30
        Constraints.MinWidth = 389
        ParentBackground = False
        TabOrder = 1
        OnEnter = PanelEnter
        OnExit = PanelExit
        OnMouseEnter = PanelMouseEnter
        DesignSize = (
          389
          88)
        object Label3: TLabel
          Left = 2
          Top = 4
          Width = 32
          Height = 13
          Caption = #1048#1097#1077#1084':'
        end
        object SpeedButton1: TSpeedButton
          Left = 365
          Top = 3
          Width = 20
          Height = 20
          Flat = True
        end
        object E1: TEdit
          Left = 40
          Top = 4
          Width = 264
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 0
          OnKeyPress = E1KeyPress
        end
        object StartSearch: TButton
          Left = 310
          Top = 4
          Width = 75
          Height = 21
          Anchors = [akTop, akRight]
          Caption = #1054#1090#1086#1073#1088#1072#1090#1100
          TabOrder = 1
          OnClick = StartSearchClick
        end
        object SearchParams: TRadioGroup
          Left = 8
          Top = 27
          Width = 198
          Height = 57
          Caption = #1048#1089#1082#1072#1090#1100' '#1087#1086':'
          Color = clBtnFace
          Columns = 2
          ItemIndex = 0
          Items.Strings = (
            #1054#1073#1086#1079#1085#1072#1095#1077#1085#1080#1102
            #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1102
            #1047#1072#1082#1072#1079#1091
            #1052#1072#1090#1077#1088#1080#1072#1083#1091)
          ParentBackground = False
          ParentColor = False
          TabOrder = 2
        end
        object Panel14: TPanel
          Left = 212
          Top = 29
          Width = 173
          Height = 56
          BevelEdges = [beLeft, beTop]
          BevelOuter = bvNone
          Caption = 'Panel5'
          TabOrder = 3
          object GroupBox3: TGroupBox
            Left = 0
            Top = 0
            Width = 173
            Height = 56
            Align = alClient
            Anchors = [akTop, akRight]
            Caption = #1057#1090#1088#1072#1085#1080#1094#1072' '#1087#1086#1080#1089#1082#1072
            Color = clBtnFace
            ParentBackground = False
            ParentColor = False
            TabOrder = 0
            object next: TSpeedButton
              Tag = 1
              Left = 58
              Top = 29
              Width = 24
              Height = 22
              AllowAllUp = True
              Flat = True
              Glyph.Data = {
                9E020000424D9E0200000000000036000000280000000E0000000E0000000100
                18000000000068020000C40E0000C40E00000000000000000001EDE9EBEDE9EB
                EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9
                EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB393939EDE9
                EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9
                EBEDE9EBEDE9EB313131292929EDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9
                EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB292929292929292929EDE9EBED
                E9EBEDE9EBEDE9EB0000EDE9EB52525242424239393931313131313131313131
                3131292929292929292929EDE9EBEDE9EBEDE9EB0000EDE9EB5A5A5A5252524A
                4A4A4A4A4A424242424242424242393939313131292929292929EDE9EBEDE9EB
                0000EDE9EB6B6B6B6B6B6B6B6B6B6363636363635A5A5A5A5A5A525252424242
                393939393939393939EDE9EB0000EDE9EB7B7B7B7B7B7B7B7B7B7B7B7B737373
                7373736B6B6B6363635A5A5A5252524A4A4A4A4A4AEDE9EB0000EDE9EB848484
                8484848484848484848484848484847B7B7B7373736B6B6B6363635A5A5AEDE9
                EBEDE9EB0000EDE9EB8C8C8C8C8C8C8C8C8C8C8C8C8C8C8C8C8C8C8484847B7B
                7B7373736B6B6BEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9
                EBEDE9EBEDE9EB8484847B7B7B737373EDE9EBEDE9EBEDE9EBEDE9EB0000EDE9
                EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB8484847B7B7BEDE9EBEDE9EBED
                E9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB84
                8484EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBED
                E9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB
                0000}
              OnClick = CngListClick
            end
            object prev: TSpeedButton
              Tag = -1
              Left = 5
              Top = 29
              Width = 24
              Height = 22
              Flat = True
              Glyph.Data = {
                9E020000424D9E0200000000000036000000280000000E0000000E0000000100
                18000000000068020000C40E0000C40E00000000000000000001EDE9EBEDE9EB
                EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9
                EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB313131EDE9EBEDE9
                EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9
                EB313131292929EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9
                EBEDE9EBEDE9EBEDE9EB393939313131292929EDE9EBEDE9EBEDE9EBEDE9EBED
                E9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EB4A4A4A42424239393931313129
                2929292929292929292929292929292929EDE9EB0000EDE9EBEDE9EB6363635A
                5A5A5252524A4A4A424242393939393939313131292929292929313131EDE9EB
                0000EDE9EB6B6B6B6B6B6B6B6B6B6B6B6B6363635A5A5A5252525252524A4A4A
                424242424242393939EDE9EB0000EDE9EB7B7B7B7B7B7B7B7B7B7B7B7B737373
                6B6B6B6B6B6B6B6B6B6363635A5A5A5252524A4A4AEDE9EB0000EDE9EBEDE9EB
                8484848484848484848484847B7B7B7B7B7B7373737373736B6B6B6363635A5A
                5AEDE9EB0000EDE9EBEDE9EBEDE9EB8C8C8C8C8C8C8C8C8C8484848484847B7B
                7B7B7B7B7373737373736B6B6BEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EB8C8C
                8C8C8C8C848484EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9
                EBEDE9EBEDE9EBEDE9EBEDE9EB8C8C8C848484EDE9EBEDE9EBEDE9EBEDE9EBED
                E9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB848484ED
                E9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB0000EDE9EBEDE9EBEDE9EBED
                E9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EBEDE9EB
                0000}
              OnClick = CngListClick
            end
            object E2: TLabeledEdit
              Left = 32
              Top = 30
              Width = 24
              Height = 21
              EditLabel.Width = 24
              EditLabel.Height = 13
              EditLabel.Caption = #1051#1080#1089#1090
              NumbersOnly = True
              TabOrder = 0
              Text = '1'
              OnChange = E2Change
            end
            object E3: TLabeledEdit
              Left = 84
              Top = 30
              Width = 81
              Height = 21
              EditLabel.Width = 78
              EditLabel.Height = 13
              EditLabel.Caption = #1057#1090#1088#1086#1082' '#1085#1072' '#1083#1080#1089#1090#1077
              MaxLength = 4
              NumbersOnly = True
              TabOrder = 1
              Text = '20'
              OnChange = E3Change
            end
          end
        end
      end
    end
  end
  object Panel19: TPanel
    Left = 0
    Top = 448
    Width = 844
    Height = 198
    Align = alBottom
    BevelOuter = bvNone
    Caption = #1060#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1077' '#1087#1086#1090#1088#1077#1073#1085#1086#1089#1090#1080' '#1074' '#1084#1072#1090#1077#1088#1080#1072#1083#1077
    Constraints.MinHeight = 50
    TabOrder = 1
    object PageControl2: TPageControl
      Left = 0
      Top = 0
      Width = 844
      Height = 198
      ActivePage = TabSheet7
      Align = alClient
      MultiLine = True
      TabOrder = 0
      object TabSheet7: TTabSheet
        Caption = #1044#1077#1090#1072#1083#1080#1079#1072#1094#1080#1103' '#1080#1089#1087#1086#1083#1100#1079#1086#1074#1072#1085#1080#1103' '#1084#1072#1090#1077#1088#1080#1072#1083#1072' '#1074' '#1079#1072#1082#1072#1079#1077
        object Mater_detail: TStringGrid
          Left = 0
          Top = 0
          Width = 836
          Height = 170
          Align = alClient
          BevelEdges = [beBottom]
          BevelInner = bvNone
          BevelOuter = bvNone
          TabOrder = 0
        end
      end
      object TabSheet8: TTabSheet
        Caption = #1055#1086#1090#1088#1077#1073#1085#1086#1089#1090#1100' '#1074' '#1084#1072#1090#1077#1088#1080#1072#1083#1072#1093
        ImageIndex = 1
        object potr_materials: TStringGrid
          Left = 0
          Top = 0
          Width = 836
          Height = 170
          Align = alClient
          BevelInner = bvNone
          BevelOuter = bvNone
          TabOrder = 0
        end
      end
      object TabSheet9: TTabSheet
        Caption = #1056#1072#1079#1088#1077#1096#1077#1085#1080#1103' '#1085#1072' '#1080#1089#1087#1086#1083#1100#1079#1086#1074#1072#1085#1080#1077' '#1076#1088#1091#1075#1080#1093' '#1084#1072#1090#1077#1088#1080#1072#1083#1086#1074
        ImageIndex = 2
        object Change_materials: TStringGrid
          Left = 0
          Top = 0
          Width = 836
          Height = 170
          Align = alClient
          BevelInner = bvNone
          BevelOuter = bvNone
          TabOrder = 0
        end
      end
    end
  end
  object ADC: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Password=q23s10z56;Persist Security Info=True' +
      ';User ID=root;Data Source=yzpm;Initial Catalog=administration'
    Provider = 'MSDASQL.1'
    Left = 248
    Top = 200
  end
  object PAB1: TPopupActionBar
    Left = 152
    Top = 152
    object N8: TMenuItem
      Caption = #1059#1079#1077#1083
      object N9: TMenuItem
        Caption = #1056#1072#1089#1082#1088#1099#1090#1100
        OnClick = N9Click
      end
      object N10: TMenuItem
        Caption = #1057#1074#1077#1088#1085#1091#1090#1100
        OnClick = N10Click
      end
    end
    object N18: TMenuItem
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      OnClick = N18Click
    end
  end
end
