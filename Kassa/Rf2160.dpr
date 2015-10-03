program Rf2160;

uses
  Forms,
  SysUtils,
  Unit1 in 'Unit1.pas' {Form1},
  rfUnit in 'rfUnit.pas',
  rfReq in 'rfReq.pas',
//  ConnectionParams in 'ConnectionParams.pas' {FormConnectionParams},
  HcTLB_TLB in 'HcTLB_TLB.pas';

{$R *.res}

begin
  Application.Initialize;
  try
      Application.CreateForm(TForm1, Form1);
  Application.Run;
  except
  on E: Exception do
  begin
       Application.MessageBox(PAnsiChar(E.Message), 'Фатальная ошибка');
       Halt;
  end;
  end;
end.
