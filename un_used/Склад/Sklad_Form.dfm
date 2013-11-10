object Sklad: TSklad
  Left = 0
  Top = 0
  Caption = #1057#1082#1083#1072#1076
  ClientHeight = 590
  ClientWidth = 768
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
    Width = 768
    Height = 590
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1042#1080#1076' '#1085#1072' '#1074#1082#1083#1072#1076#1082#1091' '#1076#1083#1103' '#1088#1072#1073#1086#1090#1099' '#1089' '#1089#1086#1076#1077#1088#1078#1080#1084#1099#1084' '#1089#1082#1083#1072#1076#1072
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 760
        Height = 137
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object View_Kont: TPanel
          Left = 0
          Top = 0
          Width = 225
          Height = 137
          Align = alLeft
          BevelEdges = [beLeft, beTop, beBottom]
          BevelKind = bkTile
          BevelOuter = bvNone
          TabOrder = 0
          object Image1: TImage
            Left = 4
            Top = 4
            Width = 213
            Height = 106
            OnClick = R_GraphClick
          end
          object Label6: TLabel
            Left = 2
            Top = 116
            Width = 215
            Height = 13
            Caption = #1044#1083#1103' '#1091#1074#1077#1083#1080#1095#1077#1085#1080#1103' '#1085#1072#1078#1084#1080#1090#1077' '#1085#1072' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077
          end
        end
        object Panel7: TPanel
          Left = 225
          Top = 0
          Width = 415
          Height = 137
          Align = alClient
          BevelKind = bkTile
          BevelOuter = bvNone
          Caption = #1048#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077' '#1082#1072#1088#1090#1099' '#1089#1082#1083#1072#1076#1072'/'#1089#1087#1080#1089#1086#1082' '#1103#1095#1077#1077#1082' '#1089#1082#1083#1072#1076#1072
          TabOrder = 1
          OnClick = Panel7Click
        end
        object View_Zagr: TPanel
          Left = 640
          Top = 0
          Width = 120
          Height = 137
          Align = alRight
          BevelEdges = [beTop, beRight, beBottom]
          BevelKind = bkTile
          BevelOuter = bvNone
          TabOrder = 2
          object Free_percent: TLabel
            Left = 82
            Top = 90
            Width = 17
            Height = 13
            Caption = '0%'
          end
          object Label2: TLabel
            Left = 26
            Top = 90
            Width = 50
            Height = 13
            Caption = #1057#1074#1086#1073#1086#1076#1085#1086
          end
          object Use_percent: TLabel
            Left = 82
            Top = 112
            Width = 29
            Height = 13
            Caption = '100%'
          end
          object Label5: TLabel
            Left = 26
            Top = 112
            Width = 36
            Height = 13
            Caption = #1047#1072#1085#1103#1090#1086
          end
          object R_Graph: TImage
            Left = 4
            Top = 4
            Width = 109
            Height = 80
            OnClick = R_GraphClick
          end
          object Panel16: TPanel
            Left = 4
            Top = 90
            Width = 16
            Height = 16
            Color = clFuchsia
            ParentBackground = False
            TabOrder = 0
          end
          object Panel21: TPanel
            Left = 4
            Top = 112
            Width = 16
            Height = 16
            Color = clBlue
            ParentBackground = False
            TabOrder = 1
          end
        end
      end
      object Panel5: TPanel
        Left = 0
        Top = 137
        Width = 760
        Height = 425
        Align = alClient
        BevelEdges = [beLeft, beTop, beRight]
        BevelKind = bkTile
        BevelOuter = bvNone
        TabOrder = 1
        object Splitter1: TSplitter
          Left = 0
          Top = 352
          Width = 756
          Height = 5
          Cursor = crVSplit
          Align = alBottom
          Beveled = True
          ExplicitTop = 202
          ExplicitWidth = 729
        end
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 756
          Height = 352
          Align = alClient
          BevelOuter = bvNone
          Caption = #1057#1087#1080#1089#1086#1082' '#1084#1072#1090#1077#1088#1080#1072#1083#1086#1074' '#1085#1072' '#1089#1082#1083#1072#1076#1077' ('#1086#1087#1094#1080#1103' '#1079#1072#1082#1072#1079#1072#1090#1100' '#1084#1072#1090#1077#1088#1080#1072#1083')'
          TabOrder = 0
          object Panel8: TPanel
            Left = 0
            Top = 0
            Width = 756
            Height = 25
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 0
            object Panel9: TPanel
              Left = 0
              Top = 0
              Width = 756
              Height = 25
              Align = alClient
              BevelOuter = bvNone
              TabOrder = 0
              DesignSize = (
                756
                25)
              object Label4: TLabel
                Left = 6
                Top = 4
                Width = 102
                Height = 13
                Caption = #1048#1089#1082#1072#1090#1100' '#1084#1072#1090#1077#1088#1080#1072#1083' '#1087#1086
              end
              object Label1: TLabel
                Left = 511
                Top = 6
                Width = 86
                Height = 13
                Anchors = [akTop, akRight]
                Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1087#1086':'
              end
              object Edit1: TEdit
                Left = 265
                Top = 2
                Width = 240
                Height = 21
                Anchors = [akLeft, akTop, akRight]
                TabOrder = 0
                Text = 'Edit1'
              end
              object Find_params: TComboBox
                Left = 114
                Top = 2
                Width = 145
                Height = 21
                Style = csDropDownList
                ItemIndex = 0
                TabOrder = 1
                Text = #1048#1085#1074#1077#1085#1090#1072#1088#1085#1086#1084#1091' '#1085#1086#1084#1077#1088#1091
                Items.Strings = (
                  #1048#1085#1074#1077#1085#1090#1072#1088#1085#1086#1084#1091' '#1085#1086#1084#1077#1088#1091
                  #1050#1086#1076#1091' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
                  #1053#1072#1079#1074#1072#1085#1080#1102
                  #1055#1088#1080#1084#1077#1085#1077#1085#1080#1102)
              end
              object Sort_Params: TComboBox
                Left = 603
                Top = 2
                Width = 148
                Height = 21
                Style = csDropDownList
                Anchors = [akTop, akRight]
                ItemIndex = 0
                TabOrder = 2
                Text = #1050#1086#1076#1091' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
                Items.Strings = (
                  #1050#1086#1076#1091' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
                  #1048#1085#1074#1077#1088#1090#1072#1088#1085#1086#1084#1091' '#1085#1086#1084#1077#1088#1091
                  #1047#1072#1075#1088#1091#1078#1077#1085#1085#1086#1089#1090#1080
                  '...')
              end
            end
          end
          object StringGrid1: TStringGrid
            Left = 0
            Top = 25
            Width = 756
            Height = 327
            Align = alClient
            TabOrder = 1
          end
        end
        object Panel3: TPanel
          Left = 0
          Top = 357
          Width = 756
          Height = 66
          Align = alBottom
          BevelOuter = bvNone
          Caption = 
            #1057#1087#1080#1089#1086#1082' '#1076#1077#1090#1072#1083#1077#1081' '#1074' '#1082#1086#1090#1086#1088#1099#1093' '#1087#1088#1080#1084#1077#1085#1103#1077#1090#1089#1103' '#1084#1072#1090#1077#1088#1080#1072#1083' '#1087#1086#1082#1072#1079#1099#1074#1072#1090#1100' '#1073#1086#1083#1100#1096#1077' ' +
            '1 '#1089#1090#1088#1086#1082#1080' '#1087#1088#1080' '#1085#1072#1083#1080#1095#1080#1080' '#1080#1085#1092#1086'. '#1080#1085#1072#1095#1077' '#1086#1090#1086#1073#1088#1072#1078#1072#1090#1100' '#1090#1086#1083#1100#1082#1086' 1 '#1089#1090#1088#1086#1082#1091' '#1085#1086' '#1085 +
            #1077' '#1073#1086#1083#1100#1096#1077' 70% '#1076#1086#1089#1090#1091#1087#1085#1086#1081' '#1074#1099#1089#1086#1090#1099' '#1073#1072#1079#1086#1074#1086#1075#1086' '#1082#1086#1085#1090#1077#1081#1085#1077#1088#1072
          TabOrder = 1
          object StringGrid2: TStringGrid
            Left = 0
            Top = 0
            Width = 756
            Height = 66
            Align = alClient
            TabOrder = 0
          end
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1044#1080#1072#1083#1086#1075' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103'/'#1074#1085#1077#1089#1077#1085#1080#1103' '#1080#1079#1084#1077#1085#1077#1085#1080#1081
      ImageIndex = 1
      object Panel11: TPanel
        Left = 0
        Top = 3
        Width = 730
        Height = 105
        Caption = 
          #1055#1088#1077#1076#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086' '#1089#1090#1088#1086#1082#1072' '#1087#1086#1103#1074#1083#1103#1090#1100#1089#1103' '#1073#1091#1076#1077#1090' '#1087#1086' '#1085#1077#1086#1073#1093#1086#1076#1080#1084#1086#1089#1090#1080' '#1074' '#1075#1083#1072#1074 +
          #1085#1086#1084' '#1086#1082#1085#1077' '#1085#1072#1073#1086#1088' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074' '#1076#1083#1103' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103'/'#1074#1085#1077#1089#1077#1085#1080#1103' '#1074' '#1073#1072#1079#1091
        TabOrder = 0
      end
      object Panel12: TPanel
        Left = 0
        Top = 114
        Width = 730
        Height = 105
        Caption = #1055#1088#1077#1076#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086' '#1089#1090#1088#1086#1095#1082#1072' '#1076#1080#1072#1083#1086#1075' '#1076#1083#1103' '#1089#1087#1080#1089#1082#1072#1085#1080#1103' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
        TabOrder = 1
      end
      object Panel13: TPanel
        Left = 0
        Top = 273
        Width = 730
        Height = 48
        Caption = 
          #1055#1088#1077#1076#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086' '#1089#1090#1088#1086#1095#1082#1072' '#1076#1080#1072#1083#1086#1075' '#1076#1083#1103' '#1087#1077#1088#1077#1084#1077#1097#1077#1085#1080#1103' '#1084#1072#1090#1077#1088#1080#1072#1083#1072' '#1087#1086' '#1089#1082#1083 +
          #1072#1076#1072#1084
        TabOrder = 2
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077' '#1084#1072#1090#1077#1088#1080#1072#1083#1072#1084#1080' '
      ImageIndex = 2
      object Panel20: TPanel
        Left = 0
        Top = 0
        Width = 760
        Height = 562
        Align = alClient
        BevelOuter = bvNone
        Caption = 'Panel20'
        TabOrder = 0
        object Splitter2: TSplitter
          Left = 0
          Top = 361
          Width = 760
          Height = 3
          Cursor = crVSplit
          Align = alBottom
          AutoSnap = False
          ExplicitTop = 359
        end
        object Panel18: TPanel
          Left = 0
          Top = 0
          Width = 760
          Height = 361
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 0
          object Splitter3: TSplitter
            Left = 393
            Top = 0
            Height = 361
            AutoSnap = False
            ExplicitHeight = 503
          end
          object materials_lists: TPageControl
            Left = 396
            Top = 0
            Width = 364
            Height = 361
            ActivePage = TabSheet4
            Align = alClient
            Constraints.MinWidth = 100
            TabOrder = 0
            object TabSheet4: TTabSheet
              Caption = #1057#1090#1072#1085#1076#1072#1088#1090#1085#1099#1077' '#1080#1079#1076#1077#1083#1080#1103
              object Std_izd: TStringGrid
                Left = 0
                Top = 0
                Width = 356
                Height = 333
                Align = alClient
                TabOrder = 0
              end
            end
            object TabSheet5: TTabSheet
              Caption = #1052#1072#1090#1077#1088#1080#1072#1083#1099
              ImageIndex = 1
              object Materials: TStringGrid
                Left = 0
                Top = 0
                Width = 356
                Height = 333
                Align = alClient
                TabOrder = 0
              end
            end
            object TabSheet6: TTabSheet
              Caption = #1042#1089#1087#1086#1084#1086#1075#1072#1090#1077#1083#1100#1085#1099#1077' '#1084#1072#1090#1077#1088#1080#1072#1083#1099
              ImageIndex = 2
              object Vspom_materials: TStringGrid
                Left = 0
                Top = 0
                Width = 356
                Height = 333
                Align = alClient
                BevelInner = bvNone
                BevelOuter = bvNone
                TabOrder = 0
              end
            end
          end
          object Panel15: TPanel
            Left = 0
            Top = 0
            Width = 393
            Height = 361
            Align = alLeft
            BevelKind = bkTile
            BevelOuter = bvNone
            Caption = #1057#1087#1080#1089#1086#1082' '#1079#1072#1082#1072#1079#1086#1074' '#1074' '#1079#1072#1087#1091#1089#1082#1077
            Constraints.MinHeight = 150
            Constraints.MinWidth = 390
            TabOrder = 1
            object TreeView1: TTreeView
              Left = 0
              Top = 0
              Width = 389
              Height = 267
              Align = alClient
              BevelInner = bvNone
              BevelOuter = bvNone
              BorderStyle = bsNone
              Indent = 19
              TabOrder = 0
              Items.NodeData = {
                0301000000280000000000000000000000FFFFFFFFFFFFFFFF00000000000000
                00010000000105370430043A04300437042A0000000000000000000000FFFFFF
                FFFFFFFFFF00000000000000000100000001063F0430044004420438044F042A
                0000000000000000000000FFFFFFFFFFFFFFFF00000000000000000000000001
                0634043504420430043B044C04}
              ExplicitLeft = 3
            end
            object Panel17: TPanel
              Left = 0
              Top = 267
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
                Left = 26
                Top = 5
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
                Left = 64
                Top = 4
                Width = 240
                Height = 21
                Anchors = [akLeft, akTop, akRight]
                TabOrder = 0
              end
              object StartSearch: TButton
                Left = 310
                Top = 4
                Width = 75
                Height = 21
                Anchors = [akTop, akRight]
                Caption = #1054#1090#1086#1073#1088#1072#1090#1100
                TabOrder = 1
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
                  object Snext: TSpeedButton
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
                  end
                  object Sprev: TSpeedButton
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
                  end
                  object SE2: TLabeledEdit
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
                  end
                  object SE3: TLabeledEdit
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
                  end
                end
              end
              object Button1: TButton
                Left = 0
                Top = 4
                Width = 20
                Height = 21
                ElevationRequired = True
                TabOrder = 4
              end
            end
          end
        end
        object Panel19: TPanel
          Left = 0
          Top = 364
          Width = 760
          Height = 198
          Align = alBottom
          BevelOuter = bvNone
          Caption = #1060#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1077' '#1087#1086#1090#1088#1077#1073#1085#1086#1089#1090#1080' '#1074' '#1084#1072#1090#1077#1088#1080#1072#1083#1077
          Constraints.MinHeight = 50
          TabOrder = 1
          object PageControl2: TPageControl
            Left = 0
            Top = 0
            Width = 760
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
                Width = 752
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
                Width = 752
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
                Width = 752
                Height = 170
                Align = alClient
                BevelInner = bvNone
                BevelOuter = bvNone
                TabOrder = 0
              end
            end
          end
        end
      end
    end
  end
end
