object mainFrm: TmainFrm
  Left = 0
  Top = 0
  Caption = 'TAIF StatGet'
  ClientHeight = 645
  ClientWidth = 974
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object init: TButton
    Left = 891
    Top = 16
    Width = 75
    Height = 25
    Caption = 'init'
    TabOrder = 0
    OnClick = initClick
  end
  object Button1: TButton
    Left = 800
    Top = 16
    Width = 75
    Height = 25
    Caption = 'getInfo'
    TabOrder = 1
    OnClick = Button1Click
  end
  object homeTeamFull: TEdit
    Left = 240
    Top = 45
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'homeTeamFull'
  end
  object homeTeam: TEdit
    Left = 240
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 3
    Text = 'homeTeam'
  end
  object awayTeamFull: TEdit
    Left = 424
    Top = 45
    Width = 121
    Height = 21
    TabOrder = 4
    Text = 'awayTeamFull'
  end
  object PeriodGoals: TListView
    Left = 56
    Top = 152
    Width = 697
    Height = 289
    Columns = <
      item
        Caption = 'Tid'
      end
      item
        Caption = 'Res'
      end
      item
        Caption = 'Stat'
        Width = 60
      end
      item
        Caption = 'Lag'
      end
      item
        Caption = 'M'#229'lg'#246'rare'
        Width = 160
      end
      item
        Caption = 'Assisterande 1'
        Width = 160
      end
      item
        Caption = 'Assisterande 2'
        Width = 160
      end>
    MultiSelect = True
    TabOrder = 5
    ViewStyle = vsReport
  end
  object awayTeam: TEdit
    Left = 424
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 6
    Text = 'awayTeam'
  end
  object awayShots: TEdit
    Left = 584
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 7
    Text = 'awayShots'
  end
  object homeShots: TEdit
    Left = 96
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 8
    Text = 'homeShots'
  end
  object statsAddress: TEdit
    Left = 240
    Top = 112
    Width = 305
    Height = 21
    TabOrder = 9
    Text = 'statsAddress'
  end
  object date: TEdit
    Left = 336
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 10
    Text = 'date'
  end
  object genFiles: TButton
    Left = 808
    Top = 144
    Width = 75
    Height = 25
    Caption = 'generateFiles'
    TabOrder = 11
    OnClick = genFilesClick
  end
  object penaltys: TListView
    Left = 216
    Top = 460
    Width = 337
    Height = 177
    Columns = <
      item
        Caption = 'Stat'
        Width = 70
      end
      item
        Caption = 'Res'
      end
      item
        Caption = 'Lag'
      end
      item
        Caption = 'M'#229'lg'#246'rare'
        Width = 160
      end>
    MultiSelect = True
    TabOrder = 12
    ViewStyle = vsReport
  end
  object practiceGame: TCheckBox
    Left = 96
    Top = 10
    Width = 97
    Height = 17
    Caption = 'Tr'#228'ning'
    TabOrder = 13
  end
  object round: TEdit
    Left = 167
    Top = 8
    Width = 50
    Height = 21
    TabOrder = 14
    Text = 'omg. Nr'
  end
  object resultat: TEdit
    Left = 584
    Top = 8
    Width = 73
    Height = 21
    TabOrder = 15
    Text = 'resultat'
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 752
    Top = 592
  end
  object MainMenu1: TMainMenu
    Left = 824
    Top = 368
    object tree: TMenuItem
      Caption = 'Tree'
      OnClick = treeClick
    end
  end
end
