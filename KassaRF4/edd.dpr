program edd;

uses
  Forms,
  Main in 'Main.pas' {FormMain},
  ConnectionParams in 'ConnectionParams.pas' {FormConnectionParams},
  NewItem in 'NewItem.pas' {NewPLU},
  ItfProc in 'ItfProc.pas' {ProcItfForm},
  HcTLB_TLB in 'C:\Documents and Settings\olazebnyk\Мои документы\RAD Studio\5.0\Imports\HcTLB_TLB.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TFormMain, FormMain);
  Application.Run;
end.
