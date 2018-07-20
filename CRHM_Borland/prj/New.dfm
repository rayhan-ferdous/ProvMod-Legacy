object Form1: TForm1
  Left = 402
  Top = 119
  Width = 1247
  Height = 675
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClick = FormClick
  PixelsPerInch = 96
  TextHeight = 13
  object CoolBar1: TCoolBar
    Left = 0
    Top = 10
    Width = 169
    Height = 415
    Align = alNone
    Bands = <
      item
        Control = PanelA
        ImageIndex = -1
        MinHeight = 250
        Width = 165
      end
      item
        Control = PanelB
        ImageIndex = -1
        MinHeight = 100
        Width = 165
      end
      item
        Control = PanelC
        ImageIndex = -1
        MinHeight = 60
        Width = 165
      end>
    Visible = False
    DesignSize = (
      165
      411)
    object PanelC: TPanel
      Left = 9
      Top = 354
      Width = 152
      Height = 60
      Align = alClient
      Caption = 'PanelC'
      TabOrder = 2
      object CancelScreen: TLabel
        Left = 1
        Top = 1
        Width = 150
        Height = 58
        Align = alClient
        Alignment = taCenter
        Caption = 'Cancel'
        Color = clBtnFace
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        Layout = tlCenter
        OnClick = CancelScreenClick
      end
    end
    object PanelA: TPanel
      Left = 9
      Top = 0
      Width = 152
      Height = 250
      Align = alTop
      Caption = 'PanelA'
      TabOrder = 0
      object RadioGroupFunct: TRadioGroup
        Left = 1
        Top = 1
        Width = 150
        Height = 248
        Align = alClient
        Caption = 'Select Function'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Items.Strings = (
          'Observation'
          'VP_saturated'
          'Watts to MJ/Int'
          'MJ/Int to Watts'
          'Average'
          'Minimum'
          'Maximum'
          'Total'
          'Positive'
          'First'
          'Last'
          'Count'
          'Count0'
          'Delta')
        ParentFont = False
        TabOrder = 0
        OnClick = RadioGroupFunctClick
      end
    end
    object PanelB: TPanel
      Left = 9
      Top = 252
      Width = 152
      Height = 100
      Anchors = []
      Caption = 'PanelB'
      TabOrder = 1
      object RadioGroupDisplay: TRadioGroup
        Left = 1
        Top = 1
        Width = 150
        Height = 98
        Align = alClient
        Caption = 'Select Display Mode'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Items.Strings = (
          'Display Off'
          'Display Final Value'
          'Display Working Values')
        ParentFont = False
        TabOrder = 0
        OnClick = RadioGroupDisplayClick
      end
    end
  end
end
