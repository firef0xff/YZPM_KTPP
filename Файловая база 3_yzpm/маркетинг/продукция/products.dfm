object prod: Tprod
  Left = 0
  Top = 0
  Width = 740
  Height = 637
  TabOrder = 0
  object Splitter1: TSplitter
    Left = 0
    Top = 317
    Width = 740
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 725
    ExplicitTop = 0
    ExplicitWidth = 288
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 739
    Height = 317
    Align = alClient
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 0
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 735
      Height = 64
      Align = alTop
      BevelEdges = []
      BevelKind = bkTile
      BevelOuter = bvNone
      ParentBackground = False
      TabOrder = 0
      object Panel8: TPanel
        Left = 0
        Top = 0
        Width = 179
        Height = 64
        Align = alLeft
        BevelEdges = [beRight, beBottom]
        BevelKind = bkTile
        BevelOuter = bvNone
        TabOrder = 0
        object GroupBox2: TGroupBox
          Left = 0
          Top = 0
          Width = 177
          Height = 62
          Align = alClient
          Caption = #1057#1090#1088#1072#1085#1080#1094#1072' '#1087#1086#1080#1089#1082#1072
          Color = clBtnFace
          ParentBackground = False
          ParentColor = False
          TabOrder = 0
          object next: TSpeedButton
            Tag = 1
            Left = 64
            Top = 30
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
            OnClick = nextClick
          end
          object prev: TSpeedButton
            Tag = -1
            Left = 4
            Top = 30
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
            OnClick = nextClick
          end
          object E2: TLabeledEdit
            Left = 34
            Top = 31
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
            Left = 94
            Top = 31
            Width = 80
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
      object Search: TButton
        Left = 185
        Top = 4
        Width = 168
        Height = 25
        Caption = #1055#1088#1072#1084#1072#1090#1077#1088#1080#1090#1099' '#1089#1086#1088#1090#1080#1088#1086#1074#1082#1080
        HotImageIndex = 3
        ImageIndex = 3
        Images = ImageList1
        TabOrder = 1
        OnClick = SearchClick
      end
      object Add: TButton
        Left = 185
        Top = 35
        Width = 87
        Height = 25
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        HotImageIndex = 0
        ImageIndex = 0
        Images = ImageList1
        TabOrder = 2
        OnClick = AddClick
      end
      object Edit: TButton
        Left = 278
        Top = 35
        Width = 120
        Height = 25
        Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
        HotImageIndex = 1
        ImageIndex = 1
        Images = ImageList1
        TabOrder = 3
        OnClick = EditClick
      end
      object Del: TButton
        Left = 404
        Top = 35
        Width = 69
        Height = 25
        Caption = #1059#1076#1072#1083#1080#1090#1100
        HotImageIndex = 2
        ImageIndex = 2
        Images = ImageList1
        TabOrder = 4
        OnClick = DelClick
      end
      object SortClear: TButton
        Left = 359
        Top = 4
        Width = 114
        Height = 25
        Caption = #1057#1073#1088#1086#1089' '#1089#1086#1088#1090#1080#1088#1086#1074#1082#1080
        HotImageIndex = 3
        ImageIndex = 3
        Images = ImageList1
        TabOrder = 5
        OnClick = SortClearClick
      end
    end
    object Panel5: TPanel
      Left = 0
      Top = 64
      Width = 735
      Height = 249
      Align = alClient
      BevelEdges = [beTop]
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = 'Panel1'
      TabOrder = 1
      object SG: TStringGrid
        Left = 0
        Top = 17
        Width = 735
        Height = 230
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        ColCount = 14
        DefaultColWidth = 16
        DefaultRowHeight = 16
        FixedCols = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect, goFixedRowClick, goFixedHotTrack]
        TabOrder = 0
        OnDrawCell = SGDrawCell
        OnFixedCellClick = SGFixedCellClick
        OnMouseUp = SGMouseUp
        OnSelectCell = SGSelectCell
      end
      object colgrid: TStringGrid
        Left = 0
        Top = 0
        Width = 735
        Height = 17
        Align = alTop
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        Color = clBtnFace
        ColCount = 8
        DefaultColWidth = 16
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 2
        GradientStartColor = clBtnFace
        ScrollBars = ssNone
        TabOrder = 1
      end
    end
  end
  object Panel2: TPanel
    Left = 739
    Top = 0
    Width = 1
    Height = 317
    Align = alRight
    BevelEdges = [beTop, beRight, beBottom]
    BevelKind = bkTile
    BevelOuter = bvNone
    Caption = 'Panel1'
    TabOrder = 1
  end
  object Panel3: TPanel
    Left = 0
    Top = 320
    Width = 740
    Height = 317
    Align = alBottom
    BevelEdges = [beLeft, beRight, beBottom]
    BevelKind = bkTile
    BevelOuter = bvNone
    ParentBackground = False
    TabOrder = 2
    object split: TButton
      Left = 0
      Top = 0
      Width = 736
      Height = 7
      Align = alTop
      Style = bsSplitButton
      TabOrder = 0
      OnClick = splitClick
    end
    object Panel6: TPanel
      Tag = 1
      Left = 0
      Top = 7
      Width = 736
      Height = 57
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        736
        57)
      object Label1: TLabel
        Left = 410
        Top = 87
        Width = 166
        Height = 13
        Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1103' '#1082' '#1089#1087#1077#1094#1080#1092#1080#1082#1072#1094#1080#1080
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Accept_btn: TBitBtn
        Left = 418
        Top = 22
        Width = 91
        Height = 25
        Caption = #1055#1086#1076#1087#1080#1089#1072#1085#1086
        DoubleBuffered = True
        Glyph.Data = {
          F2010000424DF201000000000000760000002800000024000000130000000100
          0400000000007C01000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333334433333
          3333333333388F3333333333000033334224333333333333338338F333333333
          0000333422224333333333333833338F33333333000033422222243333333333
          83333338F3333333000034222A22224333333338F33F33338F33333300003222
          A2A2224333333338F383F3338F33333300003A2A222A222433333338F8333F33
          38F33333000034A22222A22243333338833333F3338F333300004222A2222A22
          2433338F338F333F3338F3330000222A3A2224A22243338F3838F338F3338F33
          0000A2A333A2224A2224338F83338F338F3338F300003A33333A2224A2224338
          333338F338F3338F000033333333A2224A2243333333338F338F338F00003333
          33333A2224A2233333333338F338F83300003333333333A2224A333333333333
          8F338F33000033333333333A222433333333333338F338F30000333333333333
          A224333333333333338F38F300003333333333333A223333333333333338F8F3
          000033333333333333A3333333333333333383330000}
        ModalResult = 8
        NumGlyphs = 2
        ParentDoubleBuffered = False
        TabOrder = 0
        OnClick = Accept_btnClick
      end
      object accept_date: TEdit
        Left = 321
        Top = 24
        Width = 91
        Height = 21
        ReadOnly = True
        TabOrder = 1
      end
      object ca_name: TLabeledEdit
        Left = 4
        Top = 103
        Width = 197
        Height = 21
        EditLabel.Width = 69
        EditLabel.Height = 13
        EditLabel.Caption = #1050#1086#1085#1090#1088#1072#1075#1077#1085#1090
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object d_date: TLabeledEdit
        Left = 34
        Top = 65
        Width = 112
        Height = 21
        EditLabel.Width = 106
        EditLabel.Height = 13
        EditLabel.Caption = #1044#1072#1090#1072' '#1079#1072#1082#1083#1102#1095#1077#1085#1080#1103
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object d_num: TLabeledEdit
        Left = 4
        Top = 24
        Width = 207
        Height = 21
        EditLabel.Width = 68
        EditLabel.Height = 13
        EditLabel.Caption = #1044#1086#1075#1086#1074#1086#1088' '#8470
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        ReadOnly = True
        TabOrder = 4
        OnDblClick = dogovorClick
      end
      object d_type: TLabeledEdit
        Left = 3
        Top = 65
        Width = 20
        Height = 21
        EditLabel.Width = 25
        EditLabel.Height = 13
        EditLabel.Caption = #1074#1080#1076':'
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        EditLabel.Transparent = True
        ReadOnly = True
        TabOrder = 5
      end
      object dogovor: TButton
        Left = 73
        Top = 3
        Width = 56
        Height = 18
        Caption = #1042#1099#1073#1088#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
        OnClick = dogovorClick
      end
      object pl_ca_name: TLabeledEdit
        Left = 4
        Top = 143
        Width = 197
        Height = 21
        EditLabel.Width = 73
        EditLabel.Height = 13
        EditLabel.Caption = #1055#1083#1072#1090#1077#1083#1100#1097#1080#1082
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        ReadOnly = True
        TabOrder = 7
        OnDblClick = ca_selectClick
      end
      object gr_ca_name: TLabeledEdit
        Tag = 1
        Left = 207
        Top = 103
        Width = 197
        Height = 21
        EditLabel.Width = 103
        EditLabel.Height = 13
        EditLabel.Caption = #1043#1088#1091#1079#1086#1087#1086#1083#1091#1095#1072#1090#1077#1083#1100
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        ReadOnly = True
        TabOrder = 8
        OnDblClick = ca_selectClick
      end
      object lz_ca_name: TLabeledEdit
        Tag = 2
        Left = 207
        Top = 143
        Width = 197
        Height = 21
        EditLabel.Width = 109
        EditLabel.Height = 13
        EditLabel.Caption = #1051#1080#1079#1080#1085#1075#1087#1086#1083#1091#1095#1072#1090#1077#1083#1100
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        ReadOnly = True
        TabOrder = 9
        OnDblClick = ca_selectClick
      end
      object sp_prim: TMemo
        Left = 410
        Top = 103
        Width = 319
        Height = 61
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 10
      end
      object OK: TBitBtn
        Left = 573
        Top = 6
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = #1055#1088#1080#1085#1103#1090#1100
        DoubleBuffered = True
        Enabled = False
        Glyph.Data = {
          DE010000424DDE01000000000000760000002800000024000000120000000100
          0400000000006801000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          3333333333333333333333330000333333333333333333333333F33333333333
          00003333344333333333333333388F3333333333000033334224333333333333
          338338F3333333330000333422224333333333333833338F3333333300003342
          222224333333333383333338F3333333000034222A22224333333338F338F333
          8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
          33333338F83338F338F33333000033A33333A222433333338333338F338F3333
          0000333333333A222433333333333338F338F33300003333333333A222433333
          333333338F338F33000033333333333A222433333333333338F338F300003333
          33333333A222433333333333338F338F00003333333333333A22433333333333
          3338F38F000033333333333333A223333333333333338F830000333333333333
          333A333333333333333338330000333333333333333333333333333333333333
          0000}
        ModalResult = 1
        NumGlyphs = 2
        ParentDoubleBuffered = False
        TabOrder = 11
        OnClick = OKClick
      end
      object Cancel: TBitBtn
        Left = 654
        Top = 6
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Cancel = True
        Caption = #1054#1090#1084#1077#1085#1072
        DoubleBuffered = True
        Enabled = False
        Glyph.Data = {
          DE010000424DDE01000000000000760000002800000024000000120000000100
          0400000000006801000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          333333333333333333333333000033338833333333333333333F333333333333
          0000333911833333983333333388F333333F3333000033391118333911833333
          38F38F333F88F33300003339111183911118333338F338F3F8338F3300003333
          911118111118333338F3338F833338F3000033333911111111833333338F3338
          3333F8330000333333911111183333333338F333333F83330000333333311111
          8333333333338F3333383333000033333339111183333333333338F333833333
          00003333339111118333333333333833338F3333000033333911181118333333
          33338333338F333300003333911183911183333333383338F338F33300003333
          9118333911183333338F33838F338F33000033333913333391113333338FF833
          38F338F300003333333333333919333333388333338FFF830000333333333333
          3333333333333333333888330000333333333333333333333333333333333333
          0000}
        ModalResult = 2
        NumGlyphs = 2
        ParentDoubleBuffered = False
        TabOrder = 12
        OnClick = CancelClick
      end
      object gr_ca_select: TButton
        Tag = 1
        Left = 318
        Top = 85
        Width = 56
        Height = 18
        Caption = #1042#1099#1073#1088#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 13
        OnClick = ca_selectClick
      end
      object pl_ca_select: TButton
        Left = 78
        Top = 125
        Width = 56
        Height = 18
        Caption = #1042#1099#1073#1088#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 14
        OnClick = ca_selectClick
      end
      object lz_ca_select: TButton
        Tag = 2
        Left = 318
        Top = 125
        Width = 56
        Height = 18
        Caption = #1042#1099#1073#1088#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 15
        OnClick = ca_selectClick
      end
      object split_d: TButton
        Tag = 1
        Left = 0
        Top = 50
        Width = 736
        Height = 7
        Align = alBottom
        Style = bsSplitButton
        TabOrder = 16
        OnClick = split_dClick
      end
      object sp_date: TLabeledEdit
        Left = 217
        Top = 24
        Width = 98
        Height = 21
        EditLabel.Width = 85
        EditLabel.Height = 13
        EditLabel.Caption = #1057#1087#1077#1094#1080#1092#1080#1082#1072#1094#1080#1103
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        ReadOnly = True
        TabOrder = 17
      end
      object sp_num: TLabeledEdit
        Left = 152
        Top = 64
        Width = 98
        Height = 21
        EditLabel.Width = 101
        EditLabel.Height = 13
        EditLabel.Caption = #8470' '#1057#1087#1077#1094#1080#1092#1080#1082#1072#1094#1080#1080
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -11
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = [fsBold]
        EditLabel.ParentFont = False
        NumbersOnly = True
        ReadOnly = True
        TabOrder = 18
      end
    end
    object Panel7: TPanel
      Left = 0
      Top = 64
      Width = 736
      Height = 251
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 2
      object Panel9: TPanel
        Left = 0
        Top = 0
        Width = 736
        Height = 80
        Align = alTop
        BevelEdges = []
        BevelKind = bkTile
        BevelOuter = bvNone
        ParentBackground = False
        TabOrder = 0
        object Label2: TLabel
          Left = 440
          Top = 4
          Width = 40
          Height = 13
          Caption = #1053#1044#1057', %'
        end
        object Label3: TLabel
          Left = 496
          Top = 5
          Width = 39
          Height = 13
          Caption = #1042#1072#1083#1102#1090#1072
        end
        object Label4: TLabel
          Left = 551
          Top = 5
          Width = 24
          Height = 13
          Caption = #1050#1091#1088#1089
        end
        object Panel10: TPanel
          Left = 0
          Top = 0
          Width = 179
          Height = 80
          Align = alLeft
          BevelEdges = [beRight, beBottom]
          BevelKind = bkTile
          BevelOuter = bvNone
          TabOrder = 0
          object GroupBox1: TGroupBox
            Left = 0
            Top = 0
            Width = 177
            Height = 78
            Align = alClient
            Caption = #1057#1090#1088#1072#1085#1080#1094#1072' '#1087#1086#1080#1089#1082#1072
            Color = clBtnFace
            ParentBackground = False
            ParentColor = False
            TabOrder = 0
            object sp_next: TSpeedButton
              Tag = 1
              Left = 64
              Top = 40
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
              OnClick = sp_nextClick
            end
            object sp_prev: TSpeedButton
              Tag = -1
              Left = 4
              Top = 40
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
              OnClick = sp_nextClick
            end
            object sp_E2: TLabeledEdit
              Left = 34
              Top = 41
              Width = 24
              Height = 21
              EditLabel.Width = 24
              EditLabel.Height = 13
              EditLabel.Caption = #1051#1080#1089#1090
              NumbersOnly = True
              TabOrder = 0
              Text = '1'
              OnChange = sp_E2Change
            end
            object sp_E3: TLabeledEdit
              Left = 94
              Top = 41
              Width = 80
              Height = 21
              EditLabel.Width = 78
              EditLabel.Height = 13
              EditLabel.Caption = #1057#1090#1088#1086#1082' '#1085#1072' '#1083#1080#1089#1090#1077
              MaxLength = 4
              NumbersOnly = True
              TabOrder = 1
              Text = '20'
              OnChange = sp_E3Change
            end
          end
        end
        object sp_sum: TLabeledEdit
          Left = 185
          Top = 19
          Width = 121
          Height = 21
          EditLabel.Width = 30
          EditLabel.Height = 13
          EditLabel.Caption = #1048#1090#1086#1075#1086
          ReadOnly = True
          TabOrder = 1
        end
        object sp_sum_nds: TLabeledEdit
          Left = 312
          Top = 19
          Width = 121
          Height = 21
          EditLabel.Width = 103
          EditLabel.Height = 13
          EditLabel.Caption = #1048#1090#1086#1075#1086' '#1074#1082#1083#1102#1095#1072#1103' '#1053#1044#1057
          ReadOnly = True
          TabOrder = 2
        end
        object nds: TComboBox
          Left = 439
          Top = 19
          Width = 50
          Height = 21
          Style = csDropDownList
          TabOrder = 3
        end
        object valute: TComboBox
          Left = 495
          Top = 20
          Width = 50
          Height = 21
          Style = csDropDownList
          TabOrder = 4
          OnChange = valuteChange
        end
        object curs: TEdit
          Left = 551
          Top = 20
          Width = 50
          Height = 21
          TabOrder = 5
        end
        object Add_zak: TButton
          Left = 183
          Top = 46
          Width = 87
          Height = 25
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          HotImageIndex = 0
          ImageIndex = 0
          Images = ImageList1
          TabOrder = 6
        end
        object Edit_zak: TButton
          Left = 276
          Top = 46
          Width = 120
          Height = 25
          Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
          HotImageIndex = 1
          ImageIndex = 1
          Images = ImageList1
          TabOrder = 7
        end
        object Del_zak: TButton
          Left = 402
          Top = 46
          Width = 69
          Height = 25
          Caption = #1059#1076#1072#1083#1080#1090#1100
          HotImageIndex = 2
          ImageIndex = 2
          Images = ImageList1
          TabOrder = 8
        end
      end
      object SG2: TStringGrid
        Left = 0
        Top = 80
        Width = 736
        Height = 171
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        ColCount = 15
        DefaultColWidth = 16
        DefaultRowHeight = 16
        FixedCols = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect]
        TabOrder = 1
        OnDrawCell = SG2DrawCell
      end
    end
  end
  object ImageList1: TImageList
    Left = 480
    Top = 96
    Bitmap = {
      494C010104000A00040010001000FFFFFFFFFF00FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000002000000001002000000000000020
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E2C0A900CC8D6600BF70
      3F00BC6A3600BC6A3600BC6A3600BC693500BC693500BB683400BB683400BB68
      3400BD6D3B00C98A6200E3C2AD000000000000000000E2C0A900CC8D6600BF70
      3F00BC6A3600BC6A3600BC6A3600BC693500BC693500BB683400BB683400BB68
      3400BD6D3B00C98A6200E3C2AD00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C47C4D00F8F1E900F7EC
      DF00F6EADD00F6EADD00F6EADD00F6EADD00FAF2EA00FAF2EA00FAF2EA00FCF7
      F300FCF8F400FEFEFD00C27A4D000000000000000000C47C4D00F8F1E900F7EC
      DF00F6EADD00F6EADD00F6EADD00F6EADD00FAF2EA00FAF2EA00FAF2EA00FCF7
      F300FCF8F400FEFEFD00C27A4D00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C1763F00F5EBDF00FDBF
      6800FCBD6700FBBE6500FCBE6400FCBE6400FCBC6200FBBC6200FBBC6200FCBE
      6000FCBC6200FDFBF900BC6A36000000000000000000C1763F00F5EBDF00FDBF
      6800FCBD6700FBBE6500FCBE6400FCBE6400FCBC6200FBBC6200FBBC6200FCBE
      6000FCBC6200FDFBF800BC6A3600000000000000000000000000000000000000
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF0000000000000000003E39340039343000332F
      2B002C29250027242100201D1B00E7E7E700323030000B0A0900070706000404
      03000000000000000000000000000000000000000000C27C4200F7EDE300FDC2
      6E00184257002B6187004C89BC00709FB300E3C99A00FFD69500FFD59400FFD4
      9300FBBE6500FBF7F400BD6B37000000000000000000C27C4200F7EDE300FDC2
      6E00FFD8A000FFD79E00FFD69900FFD69900FFD69500FFD69500FFD59400FFD4
      9300FBBE6500FBF7F400BD6B37000000000000000000000000000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000046413B00857A7000C3B8
      AE007C7268007F756B0036322D00F1F1F1004C49470095897D00BAAEA2007C72
      68007F756B0001010100000000000000000000000000C5804500F7F0E600F8B4
      55002E66820094C7F90091C9F9004185C9002668A600D2A86500F7B25100F7B2
      4F00F7B24F00FCF8F400C1733C000000000000000000C5804500F7F0E600F8B4
      5500F7B45500F7B45500F8B45300F8B25300F7B25100F7B25100F7B25100F7B2
      4F00F7B24F00FCF8F400C1733C000000000000000000000000000000FF000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000FF000000000000000000000000004D47410083786F00CCC3
      BA00786F65007B716700332F2D00FEFEFE002C2A270095897D00C2B8AD00786F
      65007C72680006050500000000000000000000000000C6834700F8F1E900FEE5
      D5004389AA00E0F2FF00549AD8001A7ABE004998C500488CC200DAD2CD00FBE0
      C800FBE0C800FDFAF700C27A41000000000000000000C6834700F8F1E900FEE5
      D500FDE5D300FDE5D300FCE4D100FCE4D100FCE4D100FCE2CD00FCE2CD00FBE0
      C900FBE0C900FDFAF700C27A4100000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      00000000FF0000000000000000000000000000000000554E480083786F00CCC3
      BA007970660071685F00575450000000000048464400857A7000C2B8AD00786F
      65007B7167000C0B0A00000000000000000000000000C6854A00F8F2EB00FEE7
      D600A6B6BF007AB6D50090B7D10055C9E4005BDFF50078D0ED00519BD900E1D6
      CD00FBE0C800FBF7F200C68045000000000000000000C6854A00F8F2EB00FEE7
      D600FDE6D500FDE6D500FDE6D500FDE6D500FDE5D300FCE4D100FCE2CD00FBE0
      C900FBE0C900FBF7F200C6804500000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000000000000000
      FF000000FF0000000000000000000000000000000000807A76009F928600CCC3
      BA00C0B4AA00A6988B007F7C79000000000073726F0090847900C2B8AD00C0B4
      AA00A89B8E0049474600000000000000000000000000C7874C00F9F3EC00FEE8
      D600FEE8D600B3C6CC0076B9D600C2F6FD0063DFF7005DE2F80079D3F0004998
      DA00E2D5C800FAF2EA00C78347000000000000000000C7874C00F9F3EC00FEE8
      D600FEE8D600FDE6D500FDE6D500FDE6D500FDE5D300FBE4D000FBE3CD00FADF
      C600FADFC600FAF2EA00C7834700000000000000000000000000000000000000
      0000000000000000FF000000FF000000FF0000000000000000000000FF000000
      FF0000000000000000000000000000000000FCFCFC005F595200423D38005851
      4A003D383300332F2B0039363400D3D3D2005F5D5B001A181600252220001917
      15000F0E0D0011111100FDFCFC000000000000000000C78B4E00F9F4EE00FEE8
      D800FEE8D800FEE8D600B0C6CC0077CBE700C7F7FD005EDCF5005AE1F7007BD4
      F1004B99DB00D2DFE900C7854A000000000000000000C78B4E00F9F4EE00FEE8
      D800FEE8D800FEE8D600FEE7D600FDE5D300FCE4D100FBE1CC00FAE0C700F9DD
      C300F8DCC200FAF4EE00C7854A00000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000FF000000FF000000FF000000
      000000000000000000000000000000000000FDFCFC009D918500B1A396007F75
      6B007C726800776D64006C635B002E2A2600564F480080766C007C726800776D
      640070675E0001010100FAFAFA000000000000000000C78B4E00F9F4EE00FEE7
      D600FDE6D500FDE6D500FDE6D500BDD6D50079D3EE00C7F7FD005FDCF5005BE2
      F7007AD6F20051A1E000AE8763000000000000000000C78B4E00F9F4EE00FEE7
      D600FDE6D500FDE6D500FDE6D500FCE6D200FBE1CC00FADFC600F8DCC200F6DA
      BD00F6D8BB00FAF4EE00C7864B00000000000000000000000000000000000000
      00000000000000000000000000000000FF000000FF000000FF00000000000000
      000000000000000000000000000000000000FDFCFC00B8ACA000BAAEA2008277
      6D0082776D00AA917B00BAA79400B8A59000B09781009F8D7D00836D5B007163
      570095897D0022222100FCFCFC000000000000000000C78C5000F9F4F000FCE6
      D300FCE6D400FDE7D300FCE4D100FBE3CD00BED4D0007DD4EE00C4F6FD006CDD
      F6006DCAED0063A3D7006499C800E5EEF70000000000C78C5000F9F4F000FCE6
      D200FCE6D400FDE7D300FCE4D100FBE3CD00FAE0C900F8DCC200000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000FF000000FF000000FF000000
      000000000000000000000000000000000000FCFCFC00DDDAD7009B8E82009D91
      8500867B7100564F4800504A440080766C006E665D00826C5800A6917D009484
      7400564F48008A8A8A00FEFEFE000000000000000000C78C5000F9F4F000FCE3
      CD00FBE4D000FCE4CF00FCE3CD00FAE1CA00F9DDC400AFCDC90081D5EE00B2E3
      F9008BC0E700AED3F600C4E0FC006AA2D40000000000C78C5000F9F4F000FCE2
      CD00FBE4D000FCE4CF00FCE2CD00FAE0C900F9DDC400F6D9BC00000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000FF000000FF000000FF0000000000000000000000FF000000
      FF00000000000000000000000000000000000000000000000000746B6200A497
      8A0095897D009F9286003E393400000000004C4640007E746A00857A70003E39
      340085817D00F4F4F400FDFCFC000000000000000000C88D5200F9F4F000FCE3
      CD00FBE3CD00FBE3CD00FBE2CA00F9E0C800F8DCC200F5D6BA00AFE3F10077BE
      E700B4D2F000E5F3FF00ACD2EF005896CC0000000000C88D5200F9F4F000FCE2
      CD00FBE3CD00FBE3CD00FBE2CA00F9E0C800F8DCC200F5D6BA000000FF000000
      FF000000FF000000FF000000FF000000FF000000000000000000000000000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      00009A918700C3B8AE00655D5500000000007C726800A89B8E00A69A90000000
      00000000000000000000000000000000000000000000C9915900FAF6F200FAE0
      C700FBE0C800FBE2CA00FBE0C800F9DFC500F8DBC100F4D6B800FFFBF800B6CB
      C20058A5D80085B1DB00469DD000B0D7EE0000000000C9915900FAF6F200FAE0
      C700FBE0C900FBE2CA00FBE0C900F9DFC500F8DBC100F4D6B8000000FF000000
      FF000000FF000000FF000000FF000000FF0000000000000000000000FF000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      0000A79B9100BCB0A4009D91850000000000AEA093009D9185007B746D000000
      00000000000000000000000000000000000000000000D1A17300F7F2EC00F8F4
      ED00F8F4ED00F8F2EC00F8F2EC00F8F2EC00F8F2EC00F7F2EC00F2E6D700E2B2
      7D00DC986B00FCFAF900000000000000000000000000D1A17300F7F2EC00F8F4
      ED00F8F4ED00F8F2EC00F8F2EC00F8F2EC00F8F2EC00F7F2EC00000000000000
      00000000FF000000FF00000000000000000000000000000000000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E7CEB800D6A97C00CB93
      5A00C9905400C98F5400C98F5400C9905400CA8F5400C88E5400CE9C6900DDB1
      8F00FDFBF90000000000000000000000000000000000E7CEB800D6A97C00CB93
      5A00C9905400C98F5400C98F5400C9905400CA8F5400C88E5400000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000200000000100010000000000000100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000080018001FFFFFFFF80018001FFFFFFFF
      80018001EFFD800380018001C7FF800380018001C3FB800380018001E3F78103
      80018001F1E7810380018001F8CF000180018001FC1F000180018001FE3F0001
      80008033FC1F000180008033F8CFC10180008000E1E7F11F80008000C3F3F11F
      80038033C7FDFFFF80078033FFFFFFFF}
  end
end
