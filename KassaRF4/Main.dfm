object FormMain: TFormMain
  Left = 208
  Top = 104
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  ActiveControl = Button1
  Caption = 
    'EQL Delphi Demo http://help-micro.com.ua http://help-micro.kiev.' +
    'ua'
  ClientHeight = 453
  ClientWidth = 680
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 153
    Top = 0
    Width = 527
    Height = 453
    Align = alClient
    TabOrder = 0
    object m1: TMemo
      Left = 0
      Top = 0
      Width = 523
      Height = 449
      Align = alClient
      TabOrder = 0
      ExplicitLeft = -1
      ExplicitTop = -1
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 153
    Height = 453
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    object Button1: TButton
      Left = 16
      Top = 16
      Width = 121
      Height = 25
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1077
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 16
      Top = 48
      Width = 121
      Height = 25
      Caption = #1055#1088#1086#1095#1080#1090#1072#1090#1100' '#1083#1077#1085#1090#1091
      Enabled = False
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 16
      Top = 80
      Width = 121
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1090#1086#1074#1072#1088
      Enabled = False
      TabOrder = 2
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 16
      Top = 112
      Width = 121
      Height = 25
      Caption = #1042#1099#1079#1074#1072#1090#1100' '#1087#1088#1086#1094#1077#1076#1091#1088#1091
      Enabled = False
      TabOrder = 3
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 16
      Top = 144
      Width = 121
      Height = 25
      Caption = #1044#1072#1085#1085#1099#1077' '#1086' '#1082#1072#1089#1089#1077
      Enabled = False
      TabOrder = 4
      OnClick = Button5Click
    end
  end
end
