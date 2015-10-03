object FormConnectionParams: TFormConnectionParams
  Left = 293
  Top = 213
  HelpContext = 101
  ActiveControl = ELogNum
  BorderIcons = [biSystemMenu, biHelp]
  BorderStyle = bsDialog
  Caption = 'Connection parameters'
  ClientHeight = 122
  ClientWidth = 358
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object LabelLogNum: TLabel
    Left = 24
    Top = 16
    Width = 37
    Height = 13
    Caption = 'Number'
  end
  object LabelUser: TLabel
    Left = 24
    Top = 48
    Width = 41
    Height = 13
    Caption = 'Operator'
  end
  object LabelPassword: TLabel
    Left = 24
    Top = 80
    Width = 46
    Height = 13
    Caption = 'Password'
  end
  object ButtonOK: TButton
    Left = 264
    Top = 16
    Width = 75
    Height = 25
    HelpContext = 103
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object ButtonCancel: TButton
    Left = 264
    Top = 48
    Width = 75
    Height = 25
    HelpContext = 102
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object ELogNum: TEdit
    Left = 128
    Top = 16
    Width = 121
    Height = 21
    HelpContext = 104
    TabOrder = 2
  end
  object EUser: TEdit
    Left = 128
    Top = 48
    Width = 121
    Height = 21
    HelpContext = 106
    TabOrder = 3
  end
  object EPassword: TEdit
    Left = 128
    Top = 80
    Width = 121
    Height = 21
    HelpContext = 105
    TabOrder = 4
  end
end
