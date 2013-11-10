object tarandsrop: Ttarandsrop
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  ClientHeight = 353
  ClientWidth = 569
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 249
    Top = 65
    Width = 5
    Height = 288
    Color = clBtnFace
    ParentColor = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 65
    Width = 249
    Height = 288
    Align = alLeft
    TabOrder = 0
    object TV: TTreeView
      Left = 1
      Top = 1
      Width = 247
      Height = 286
      Align = alClient
      Indent = 19
      ReadOnly = True
      TabOrder = 0
      OnClick = TVClick
      OnDblClick = TVDblClick
      OnDeletion = TVDeletion
      OnExpanding = TVExpanding
    end
  end
  object Panel2: TPanel
    Left = 254
    Top = 65
    Width = 315
    Height = 288
    Align = alClient
    TabOrder = 1
    ExplicitLeft = 252
    ExplicitWidth = 317
    object img: TImage
      Left = 1
      Top = 1
      Width = 313
      Height = 286
      Align = alClient
      Center = True
      Proportional = True
      ExplicitLeft = 2
      ExplicitTop = 6
      ExplicitWidth = 274
      ExplicitHeight = 282
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 569
    Height = 65
    Align = alTop
    TabOrder = 2
    DesignSize = (
      569
      65)
    object LE1: TLabeledEdit
      Left = 8
      Top = 23
      Width = 386
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 145
      EditLabel.Height = 13
      EditLabel.Caption = #1042#1099#1073#1088#1072#1085#1086' '#1076#1083#1103' '#1080#1089#1087#1086#1083#1100#1079#1086#1074#1072#1085#1080#1103
      ReadOnly = True
      TabOrder = 0
    end
    object BitBtn1: TBitBtn
      Left = 490
      Top = 4
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1088#1080#1085#1103#1090#1100
      DoubleBuffered = True
      Kind = bkOK
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 1
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      Left = 409
      Top = 4
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1054#1090#1084#1077#1085#1072
      DoubleBuffered = True
      Kind = bkCancel
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 2
    end
    object BitBtn3: TBitBtn
      Left = 490
      Top = 34
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      DoubleBuffered = True
      ParentDoubleBuffered = False
      TabOrder = 3
      OnClick = BitBtn3Click
    end
  end
end
